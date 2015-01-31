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

#include <qtpulseaudio/qtpulseaudiosinkport.h>

#include <QDebug>

#include <pulse/introspect.h>

#include "qtpulseaudiodata.h"

class QtPulseAudioSinkPortPrivate
{
    friend class QtPulseAudioSinkPort;

    QtPulseAudioSinkPortPrivate(const QtPulseAudioData& pulseAudioData)
        : available(QtPulseAudio::PortUnknown),
          priority(0)
    {
        const pa_sink_port_info* portInfo =
                reinterpret_cast< const pa_sink_port_info* >(pulseAudioData.data);

        if (portInfo->available == PA_PORT_AVAILABLE_NO)
            available = QtPulseAudio::PortNotAvailable;
        else if (portInfo->available == PA_PORT_AVAILABLE_YES)
            available = QtPulseAudio::PortAvailable;

        name = QString::fromUtf8(portInfo->name);
        description = QString::fromUtf8(portInfo->description);
        priority = portInfo->priority;
    }

    QString name;
    QString description;
    QtPulseAudio::PortAvailability available;
    quint32 priority;
};

QtPulseAudioSinkPort::QtPulseAudioSinkPort(const QtPulseAudioData& pulseAudioData)
    : d(new QtPulseAudioSinkPortPrivate(pulseAudioData))
{
    qDebug() << "Discovered sink port: " << d->name;
}

QtPulseAudioSinkPort::~QtPulseAudioSinkPort()
{
    delete d;
}

QtPulseAudio::PortAvailability QtPulseAudioSinkPort::available() const
{
    return d->available;
}

QString QtPulseAudioSinkPort::description() const
{
    return d->description;
}

QString QtPulseAudioSinkPort::name() const
{
    return d->name;
}

quint32 QtPulseAudioSinkPort::priority() const
{
    return d->priority;
}
