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

#ifndef QTPULSEAUDIO_H
#define QTPULSEAUDIO_H

#include <qtpulseaudio/qtpulseaudioconfig.h>

#include <pulse/subscribe.h>

#include <QDebug>

namespace QtPulseAudio
{
    enum ConnectionState
    {
        Unknown = -1,
        Unconnected,
        Connecting,
        Connected,
        Failed
    };

    enum Facility
    {
        AllFacilities = -1,

        NoFacilities = 0,

        Sink = 1,
        Source = 2,
        SinkInput = 4,
        SourceOutput = 8,
        Module = 16,
        Client = 32,
        SampleCache = 64,
        Server = 128,
        Card = 256
    };

    Q_DECLARE_FLAGS(Facilities, Facility)

    enum StreamType
    {
        Playback,
        Record
    };
}

Q_DECLARE_METATYPE(QtPulseAudio::ConnectionState)
Q_DECLARE_METATYPE(QtPulseAudio::StreamType)

Q_DECLARE_OPERATORS_FOR_FLAGS(QtPulseAudio::Facilities)

QTPULSEAUDIO_DECL QDebug operator<<(QDebug dbg, QtPulseAudio::ConnectionState state);
QTPULSEAUDIO_DECL QDebug operator<<(QDebug dbg, QtPulseAudio::StreamType streamType);

#endif // QTPULSEAUDIO_H

