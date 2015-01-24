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

#include <qtpulseaudio/qtpulseaudioconnnection.h>

#include <pulse/introspect.h>

#include "qtpulseaudiodata.h"

class QtPulseAudioCard;
class QtPulseAudioSink;

class QtPulseAudioConnection::QtPulseAudioConnectionPrivate
{
    friend class QtPulseAudioConnection;

private:
    static void onCardsInfoList(pa_context* context, const pa_card_info* cardInfo, int eol, void* userData);
    static void onContextNotify(pa_context* context, void* userData);
    static void onSinkInfoList(pa_context* context, const pa_sink_info* sinkInfo, int eol, void* userData);

private:
    QtPulseAudioConnectionPrivate(QtPulseAudioConnection* q_ptr)
        : q(q_ptr),
          facilities(QtPulseAudio::AllFacilities),
          state(QtPulseAudio::Unconnected)
    {
    }

    ~QtPulseAudioConnectionPrivate();

    void checkFacilitiesQueried()
    {
        if (wantFacilities == queriedFacilities)
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
    QtPulseAudioData pulseAudioData;
    QtPulseAudioConnection* q;

    QtPulseAudio::Facilities facilities;

    QtPulseAudio::Facilities wantFacilities;
    QtPulseAudio::Facilities queriedFacilities;


    QtPulseAudio::ConnectionState state;
    QString server;

    QSet< QtPulseAudioCard* > cards;
    QHash< quint32, QtPulseAudioCard* > cardsByIndex;
    QHash< QString, QtPulseAudioCard* > cardsByName;

    QSet< QtPulseAudioSink* > sinks;
    QHash< quint32, QtPulseAudioSink* > sinksByIndex;
    QHash< QString, QtPulseAudioSink* > sinksByName;

    QHash< QString, QtPulseAudioStream* > streamsByName;
};

#endif // QTPULSEAUDIOCONTEXTPRIVATE_H
