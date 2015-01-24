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

#include <qtpulseaudio/qtpulseaudiostream.h>

#include <pulse/stream.h>

#include "qtpulseaudiodata.h"

class QtPulseAudioStream::QtPulseAudioStreamPrivate
{
    friend class QtPulseAudioStream;

    QtPulseAudioData* pulseAudioData;

    pa_stream* paStream;

    QtPulseAudio::StreamType streamType;

    QString name;
};

QtPulseAudioStream::QtPulseAudioStream(QtPulseAudioData* pulseAudioData,
                                       QtPulseAudio::StreamType streamType,
                                       const QString& name)
    : QObject(NULL),
      d(new QtPulseAudioStreamPrivate())
{
    d->pulseAudioData = pulseAudioData;

    d->streamType = streamType;
    d->name = name;

    d->paStream = pa_stream_new(d->pulseAudioData->context, d->name.toUtf8().data(), NULL, NULL);
}

QtPulseAudioStream::~QtPulseAudioStream()
{
    delete d;
}

