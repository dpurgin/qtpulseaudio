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

#ifndef QTPULSEAUDIOCONTEXTPRIVATE_H
#define QTPULSEAUDIOCONTEXTPRIVATE_H

#include <qtpulseaudio/qtpulseaudioconnection.h>

#include <pulse/introspect.h>
#include <pulse/thread-mainloop.h>

class QtPulseAudioCard;
class QtPulseAudioSink;
class QtPulseAudioSource;

class QtPulseAudioConnectionPrivate
{
    friend class QtPulseAudioConnection;

private:
    static void onCardsInfoList(
        pa_context* context, const pa_card_info* cardInfo, int eol, void* userData);

    static void onContextStateChange(pa_context* context, void* userData);

    static void onContextSubscription(pa_context* context, int success, void* userData);

    static void onContextSubscriptionEvent(
        pa_context* context, pa_subscription_event_type_t eventType, uint32_t idx, void* userData);

    static void onSinkInfoList(
        pa_context* context, const pa_sink_info* sinkInfo, int eol, void* userData);

    static void onSourceInfoList(
        pa_context* context, const pa_source_info* sourceInfo, int eol, void* userData);

private:
    QtPulseAudioConnectionPrivate(QtPulseAudioConnection* q_ptr)
        : context(NULL),
          mainLoop(NULL),
          mainLoopApi(NULL),
          q(q_ptr),
          facilities(QtPulseAudio::AllFacilities),
          wantFacilities(QtPulseAudio::NoFacilities),
          queriedFacilities(QtPulseAudio::NoFacilities),
          subscribed(false),
          state(QtPulseAudio::Unconnected)
    {
    }

    ~QtPulseAudioConnectionPrivate();

    void checkInitialized()
    {
        if (wantFacilities == queriedFacilities && subscribed)
            setState(QtPulseAudio::Connected);
    }

    void setState(QtPulseAudio::ConnectionState _state)
    {
        if (_state != state)
        {
            state = _state;

            emit q->stateChanged(state);

            switch (state)
            {
                case QtPulseAudio::Connecting:
                    emit q->connecting();
                    break;

                case QtPulseAudio::Connected:
                    emit q->connected();
                    break;

                case QtPulseAudio::Failed:
                    emit q->failed();
                    break;
            }
        }
    }

private:
    pa_context* context;
    pa_threaded_mainloop* mainLoop;
    pa_mainloop_api* mainLoopApi;

    QtPulseAudioConnection* q;

    QtPulseAudio::Facilities facilities;

    QtPulseAudio::Facilities wantFacilities;
    QtPulseAudio::Facilities queriedFacilities;
    bool subscribed;

    QtPulseAudio::ConnectionState state;
    QString server;

    QHash< QtPulseAudioCard*, QSharedPointer< QtPulseAudioCard > > cards;
    QHash< quint32, QtPulseAudioCard* > cardsByIndex;
    QHash< QString, QtPulseAudioCard* > cardsByName;

    QHash< QtPulseAudioSink*, QSharedPointer< QtPulseAudioSink > > sinks;
    QHash< quint32, QtPulseAudioSink* > sinksByIndex;
    QHash< QString, QtPulseAudioSink* > sinksByName;

    QHash< QtPulseAudioSource*, QSharedPointer< QtPulseAudioSource > > sources;
    QHash< quint32, QtPulseAudioSource* > sourcesByIndex;
    QHash< QString, QtPulseAudioSource* > sourcesByName;

    QHash< QString, QtPulseAudioStream* > streamsByName;
};

#endif // QTPULSEAUDIOCONTEXTPRIVATE_H
