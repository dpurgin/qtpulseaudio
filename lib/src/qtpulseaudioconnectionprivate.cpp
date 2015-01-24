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

#include <qtpulseaudio/qtpulseaudiocard.h>
#include <qtpulseaudio/qtpulseaudiosink.h>

#include "qtpulseaudiofacilityfactory.h"

QtPulseAudioConnection::QtPulseAudioConnectionPrivate::~QtPulseAudioConnectionPrivate()
{
    cardsByIndex.clear();
    cardsByName.clear();

//    qDeleteAll(cards);
}

void QtPulseAudioConnection::QtPulseAudioConnectionPrivate::onCardsInfoList(
        pa_context* context, const pa_card_info* cardInfo, int eol, void* userData)
{
    Q_UNUSED(context)

    QtPulseAudioConnectionPrivate* d = reinterpret_cast< QtPulseAudioConnectionPrivate* >(userData);

    if (!eol)
    {
        QtPulseAudioCard* card = dynamic_cast< QtPulseAudioCard* >(
                    QtPulseAudioFacilityFactory::create(QtPulseAudio::Card, cardInfo));

        d->cards.insert(card);
        d->cardsByIndex.insert(card->index(), card);
        d->cardsByName.insert(card->name(), card);
    }
    else
    {
        d->queriedFacilities |= QtPulseAudio::Card;
        d->checkFacilitiesQueried();
    }
}

void QtPulseAudioConnection::QtPulseAudioConnectionPrivate::onContextNotify(
        pa_context* context, void* userData)
{
    Q_UNUSED(context);

    QtPulseAudioConnectionPrivate* const d = reinterpret_cast< QtPulseAudioConnectionPrivate* >(userData);

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
            if (d->facilities.testFlag(QtPulseAudio::Card) ||
                    d->facilities.testFlag(QtPulseAudio::AllFacilities))
            {
                d->wantFacilities |= QtPulseAudio::Card;

                pa_operation_unref(
                    pa_context_get_card_info_list(
                        d->pulseAudioData.context,
                        &QtPulseAudioConnectionPrivate::onCardsInfoList,
                        d));
            }

            if (d->facilities.testFlag(QtPulseAudio::Sink) ||
                    d->facilities.testFlag(QtPulseAudio::AllFacilities))
            {
                d->wantFacilities |= QtPulseAudio::Sink;

                pa_operation_unref(
                    pa_context_get_sink_info_list(
                        d->pulseAudioData.context,
                        &QtPulseAudioConnectionPrivate::onSinkInfoList,
                        d));
            }

            d->checkFacilitiesQueried();

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

void QtPulseAudioConnection::QtPulseAudioConnectionPrivate::onSinkInfoList(
        pa_context *context, const pa_sink_info *sinkInfo, int eol, void *userData)
{
    Q_UNUSED(context)

    QtPulseAudioConnectionPrivate* const d =
            reinterpret_cast< QtPulseAudioConnectionPrivate* >(userData);

    if (!eol)
    {
        QtPulseAudioSink* sink = dynamic_cast< QtPulseAudioSink* >(
                    QtPulseAudioFacilityFactory::create(QtPulseAudio::Sink, sinkInfo));

        d->sinks.insert(sink);
        d->sinksByIndex.insert(sink->index(), sink);
        d->sinksByName.insert(sink->name(), sink);
    }
    else
    {
        d->queriedFacilities |= QtPulseAudio::Sink;
        d->checkFacilitiesQueried();
    }
}