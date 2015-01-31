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

#ifndef QTPULSEAUDIOSINKPORT_H
#define QTPULSEAUDIOSINKPORT_H

#include <QString>

#include <qtpulseaudio/qtpulseaudio.h>

class QtPulseAudioData;
class QtPulseAudioSinkPortPrivate;

class QtPulseAudioSinkPort
{
    friend class QtPulseAudioSinkPrivate;

    QtPulseAudioSinkPort(const QtPulseAudioData& data);
    ~QtPulseAudioSinkPort();

public:
    QtPulseAudio::PortAvailability available() const;
    QString description() const;
    QString name() const;
    quint32 priority() const;

private:
    QtPulseAudioSinkPortPrivate* const d;
};

#endif // QTPULSEAUDIOSINKPORT_H
