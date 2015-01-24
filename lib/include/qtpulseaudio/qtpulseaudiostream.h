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

#ifndef QTPULSEAUDIOSTREAM_H
#define QTPULSEAUDIOSTREAM_H

#include <qtpulseaudio/qtpulseaudioconfig.h>
#include <qtpulseaudio/qtpulseaudio.h>

#include <QObject>

class QtPulseAudioConnection;
class QtPulseAudioData;

class QTPULSEAUDIO_DECL QtPulseAudioStream : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QtPulseAudioStream)

public:
    QtPulseAudioStream(QtPulseAudioData* pulseAudioData,
                       QtPulseAudio::StreamType streamType,
                       const QString& name);
    virtual ~QtPulseAudioStream();

private:
    class QtPulseAudioStreamPrivate;
    QtPulseAudioStreamPrivate* d;
};

#endif // QTPULSEAUDIOSTREAM_H

