/*
 * This file is part of QtPulseAudio.
 * Copyright (C) 2015  Dmitriy Purgin <dpurgin@gmail.com>
 *
 * QtPulseAudio is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * QtPulseAudio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License and
 * GNU Lesser General Public License along with QtPulseAudio. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "qtpulseaudioconnectionprivate.h"

#include <QReadLocker>
#include <QWriteLocker>

#include <qtpulseaudio/qtpulseaudiocard.h>
#include <qtpulseaudio/qtpulseaudioserver.h>
#include <qtpulseaudio/qtpulseaudiosink.h>
#include <qtpulseaudio/qtpulseaudiosource.h>

#include "qtpulseaudiodata.h"
#include "qtpulseaudiofacilityfactory.h"

QtPulseAudioConnectionPrivate::~QtPulseAudioConnectionPrivate()
{
    cardsByIndex.clear();
    cardsByName.clear();

//    qDeleteAll(cards);
}

void QtPulseAudioConnectionPrivate::onCardInfo(
        pa_context* context, const pa_card_info* cardInfo, int eol, void* userData)
{
    Q_UNUSED(context)

    QtPulseAudioConnectionPrivate* d = reinterpret_cast< QtPulseAudioConnectionPrivate* >(userData);

    QWriteLocker locker(&d->lock);

    if (!eol)
    {
        QSharedPointer< QtPulseAudioCard > card(
            qtpaFacilityFactory->create(
                QtPulseAudio::Card,
                QtPulseAudioData(d->context, cardInfo)
            ).dynamicCast< QtPulseAudioCard >()
        );

        d->cards.insert(card.data(), card);
        d->cardsByIndex.insert(card->index(), card.data());
        d->cardsByName.insert(card->name(), card.data());

        if (d->state == QtPulseAudio::Connected)
            emit d->q->cardAdded(card);
    }
    else if (d->state != QtPulseAudio::Connected)
    {
        d->queriedFacilities |= QtPulseAudio::Card;
        d->checkInitialized();
    }
}

void QtPulseAudioConnectionPrivate::onContextStateChange(
        pa_context* context, void* userData)
{
    Q_UNUSED(context);

    QtPulseAudioConnectionPrivate* const d =
            reinterpret_cast< QtPulseAudioConnectionPrivate* >(userData);

    QWriteLocker locker(&d->lock);

    pa_context_state state = pa_context_get_state(context);

    switch (state)
    {
        case PA_CONTEXT_UNCONNECTED:
            d->setState(QtPulseAudio::Unconnected);
            break;

        case PA_CONTEXT_CONNECTING:
        case PA_CONTEXT_AUTHORIZING:
        case PA_CONTEXT_SETTING_NAME:
            d->setState(QtPulseAudio::Connecting);
            break;

        case PA_CONTEXT_READY:
        {
            quint32 subscriptionMask = PA_SUBSCRIPTION_MASK_NULL;

            if (d->facilities.testFlag(QtPulseAudio::Card) ||
                    d->facilities.testFlag(QtPulseAudio::AllFacilities))
            {
                d->wantFacilities |= QtPulseAudio::Card;
                subscriptionMask |= PA_SUBSCRIPTION_MASK_CARD;

                pa_operation_unref(
                    pa_context_get_card_info_list(
                        d->context,
                        &QtPulseAudioConnectionPrivate::onCardInfo,
                        d));
            }

            if (d->facilities.testFlag(QtPulseAudio::Server) ||
                    d->facilities.testFlag(QtPulseAudio::AllFacilities))
            {
                d->wantFacilities |= QtPulseAudio::Server;
                subscriptionMask |= PA_SUBSCRIPTION_MASK_SERVER;

                pa_operation_unref(
                    pa_context_get_server_info(
                        d->context,
                        &QtPulseAudioConnectionPrivate::onServerInfo,
                        d));
            }

            if (d->facilities.testFlag(QtPulseAudio::Sink) ||
                    d->facilities.testFlag(QtPulseAudio::AllFacilities))
            {
                d->wantFacilities |= QtPulseAudio::Sink;
                subscriptionMask |= PA_SUBSCRIPTION_MASK_SINK;

                pa_operation_unref(
                    pa_context_get_sink_info_list(
                        d->context,
                        &QtPulseAudioConnectionPrivate::onSinkInfo,
                        d));
            }

            if (d->facilities.testFlag(QtPulseAudio::Source) ||
                    d->facilities.testFlag(QtPulseAudio::AllFacilities))
            {
                d->wantFacilities |= QtPulseAudio::Source;
                subscriptionMask |= PA_SUBSCRIPTION_MASK_SOURCE;

                pa_operation_unref(
                    pa_context_get_source_info_list(
                        d->context,
                        &QtPulseAudioConnectionPrivate::onSourceInfo,
                        d));
            }

            pa_context_set_subscribe_callback(
                d->context,
                &QtPulseAudioConnectionPrivate::onContextSubscriptionEvent,
                d);

            pa_operation_unref(
                pa_context_subscribe(
                    d->context,
                    static_cast< pa_subscription_mask_t >(subscriptionMask),
                    &QtPulseAudioConnectionPrivate::onContextSubscription,
                    d));

            break;
        }

        case PA_CONTEXT_FAILED:
        case PA_CONTEXT_TERMINATED:
            d->setState(QtPulseAudio::Failed);
            break;

        default:
            d->setState(QtPulseAudio::Unknown);
            break;
    }
}

void QtPulseAudioConnectionPrivate::onContextSubscription(
        pa_context *context, int success, void *userData)
{
    Q_UNUSED(context)
    Q_UNUSED(success)
    Q_UNUSED(userData)

    qDebug() << "success: " << success;

    QtPulseAudioConnectionPrivate* d = reinterpret_cast< QtPulseAudioConnectionPrivate* >(userData);

    QWriteLocker locker(&d->lock);

    if (success)
        d->subscribed = true;
    else
        emit d->q->error("Unable to subscribe to events");

    d->checkInitialized();
}

void QtPulseAudioConnectionPrivate::onContextSubscriptionEvent(
        pa_context *context, pa_subscription_event_type_t eventData, uint32_t idx, void *userData)
{
    Q_UNUSED(context);

    QtPulseAudioConnectionPrivate* d = reinterpret_cast< QtPulseAudioConnectionPrivate* >(userData);

    QWriteLocker locker(&d->lock);

    int facility = (eventData & PA_SUBSCRIPTION_EVENT_FACILITY_MASK);
    int event = (eventData & PA_SUBSCRIPTION_EVENT_TYPE_MASK);

//    qDebug() << "EventType: " << event << ", idx: " << idx;

    if (facility == PA_SUBSCRIPTION_EVENT_CARD &&
            d->facilities.testFlag(QtPulseAudio::Card))
    {
        processCardEvent(event, idx, d);
    }
    else if (facility == PA_SUBSCRIPTION_EVENT_SERVER &&
             d->facilities.testFlag(QtPulseAudio::Server))
    {
        processServerEvent(event, d);
    }
    else if (facility == PA_SUBSCRIPTION_EVENT_SINK &&
             d->facilities.testFlag(QtPulseAudio::Sink))
    {
        processSinkEvent(event, idx, d);
    }
    else if (facility == PA_SUBSCRIPTION_EVENT_SOURCE &&
             d->facilities.testFlag(QtPulseAudio::Source))
    {
        processSourceEvent(event, idx, d);
    }
}

void QtPulseAudioConnectionPrivate::onServerInfo(
        pa_context* context, const pa_server_info* serverInfo, void* userData)
{
    Q_UNUSED(context)

    QtPulseAudioConnectionPrivate* const d =
            reinterpret_cast< QtPulseAudioConnectionPrivate* >(userData);

    QWriteLocker locker(&d->lock);

    d->server =
        qtpaFacilityFactory->create(
            QtPulseAudio::Server,
            QtPulseAudioData(d->context, serverInfo)
        ).dynamicCast< QtPulseAudioServer >();

    if (d->state != QtPulseAudio::Connected)
    {
        d->queriedFacilities |= QtPulseAudio::Server;
        d->checkInitialized();
    }
}

void QtPulseAudioConnectionPrivate::onSinkInfo(
        pa_context* context, const pa_sink_info* sinkInfo, int eol, void* userData)
{
    Q_UNUSED(context)

    QtPulseAudioConnectionPrivate* const d =
            reinterpret_cast< QtPulseAudioConnectionPrivate* >(userData);

    QWriteLocker locker(&d->lock);

    if (!eol)
    {
        QSharedPointer< QtPulseAudioSink > sink(
            qtpaFacilityFactory->create(
                QtPulseAudio::Sink,
                QtPulseAudioData(d->context, sinkInfo)
            ).dynamicCast< QtPulseAudioSink >()
        );

        d->sinks.insert(sink.data(), sink);
        d->sinksByIndex.insert(sink->index(), sink.data());
        d->sinksByName.insert(sink->name(), sink.data());

        if (d->state == QtPulseAudio::Connected)
            emit d->q->sinkAdded(sink);
    }
    else if (d->state != QtPulseAudio::Connected)
    {
        d->queriedFacilities |= QtPulseAudio::Sink;
        d->checkInitialized();
    }
}

void QtPulseAudioConnectionPrivate::onSourceInfo(
        pa_context* context, const pa_source_info* sourceInfo, int eol, void* userData)
{
    Q_UNUSED(context);

    QtPulseAudioConnectionPrivate* const d =
            reinterpret_cast< QtPulseAudioConnectionPrivate* >(userData);

    QWriteLocker locker(&d->lock);

    if (!eol)
    {
        QSharedPointer< QtPulseAudioSource > source(
            qtpaFacilityFactory->create(
                QtPulseAudio::Source,
                QtPulseAudioData(d->context, sourceInfo)
            ).dynamicCast< QtPulseAudioSource >()
        );

        d->sources.insert(source.data(), source);
        d->sourcesByIndex.insert(source->index(), source.data());
        d->sourcesByName.insert(source->name(), source.data());

        if (d->state == QtPulseAudio::Connected)
            emit d->q->sourceAdded(source);
    }
    else if (d->state != QtPulseAudio::Connected)
    {
        d->queriedFacilities |= QtPulseAudio::Source;
        d->checkInitialized();
    }
}

void QtPulseAudioConnectionPrivate::processCardEvent(
        int event, uint32_t idx, QtPulseAudioConnectionPrivate *d)
{
//    qDebug();

    if (event == PA_SUBSCRIPTION_EVENT_NEW)
    {
        pa_operation_unref(
            pa_context_get_card_info_by_index(
                d->context, idx, &QtPulseAudioConnectionPrivate::onCardInfo, d));
    }
    else if (event == PA_SUBSCRIPTION_EVENT_CHANGE)
    {
        QtPulseAudioCard* card = d->cardsByIndex.value(idx, NULL);

        if (card)
            card->update();
    }
    else if (event == PA_SUBSCRIPTION_EVENT_REMOVE)
    {
        QSharedPointer< QtPulseAudioCard > card(
            d->cards.value(
                d->cardsByIndex.value(idx, NULL),
                QSharedPointer< QtPulseAudioCard >()));

        if (card.isNull())
        {
            d->cardsByIndex.remove(card->index());
            d->cardsByName.remove(card->name());
            d->cards.remove(card.data());

            emit d->q->cardRemoved(card);
        }
    }
}

void QtPulseAudioConnectionPrivate::processServerEvent(
        int event, QtPulseAudioConnectionPrivate *d)
{
//    qDebug();

    if (event == PA_SUBSCRIPTION_EVENT_CHANGE && !d->server.isNull())
        d->server->update();
}

void QtPulseAudioConnectionPrivate::processSinkEvent(
        int event, uint32_t idx, QtPulseAudioConnectionPrivate *d)
{
//    qDebug();

    if (event == PA_SUBSCRIPTION_EVENT_NEW)
    {
        pa_operation_unref(
            pa_context_get_sink_info_by_index(
                d->context, idx, &QtPulseAudioConnectionPrivate::onSinkInfo, d));
    }
    else if (event == PA_SUBSCRIPTION_EVENT_CHANGE)
    {
        QtPulseAudioSink* sink = d->sinksByIndex.value(idx, NULL);

        if (sink)
            sink->update();
    }
    else if (event == PA_SUBSCRIPTION_EVENT_REMOVE)
    {
        QSharedPointer< QtPulseAudioSink > sink(
            d->sinks.value(
                d->sinksByIndex.value(idx, NULL),
                QSharedPointer< QtPulseAudioSink >()));

        if (!sink.isNull())
        {
            d->sinksByIndex.remove(sink->index());
            d->sinksByName.remove(sink->name());
            d->sinks.remove(sink.data());

            emit d->q->sinkRemoved(sink);
        }
    }
}

void QtPulseAudioConnectionPrivate::processSourceEvent(
        int event, uint32_t idx, QtPulseAudioConnectionPrivate *d)
{
//    qDebug();

    if (event == PA_SUBSCRIPTION_EVENT_NEW)
    {
        pa_operation_unref(
            pa_context_get_source_info_by_index(
                d->context, idx, &QtPulseAudioConnectionPrivate::onSourceInfo, d));
    }
    else if (event == PA_SUBSCRIPTION_EVENT_CHANGE)
    {
        QtPulseAudioSource* source = d->sourcesByIndex.value(idx, NULL);

        if (source)
            source->update();
    }
    else if (event == PA_SUBSCRIPTION_EVENT_REMOVE)
    {
        QSharedPointer< QtPulseAudioSource > source(
            d->sources.value(
                d->sourcesByIndex.value(idx, NULL),
                QSharedPointer< QtPulseAudioSource >()));

        if (source.isNull())
        {
            d->sourcesByIndex.remove(source->index());
            d->sourcesByName.remove(source->name());
            d->sources.remove(source.data());

            emit d->q->sourceRemoved(source);
        }
    }
}
