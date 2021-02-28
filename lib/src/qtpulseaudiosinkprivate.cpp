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

#include "qtpulseaudiosinkprivate.h"

#include <QWriteLocker>

QtPulseAudioSinkPrivate::QtPulseAudioSinkPrivate(const QtPulseAudioData& pulseAudioData)
    : QtPulseAudioFacilityPrivate(pulseAudioData),
      activePort(NULL)
{
    const pa_sink_info* sinkInfo = reinterpret_cast< const pa_sink_info* >(pulseAudioData.data);

    index = sinkInfo->index;
    name = QString::fromUtf8(sinkInfo->name);

    for (quint32 i = 0; i < sinkInfo->n_ports; i++)
    {
        QtPulseAudioSinkPort* port =
            new QtPulseAudioSinkPort(QtPulseAudioData(pulseAudioData.context, sinkInfo->ports[i]));

        ports.insert(port);
        portsByName.insert(port->name(), port);
    }

    if (sinkInfo->active_port)
        activePort = portsByName.value(QString::fromUtf8(sinkInfo->active_port->name), NULL);
}

QtPulseAudioSinkPrivate::~QtPulseAudioSinkPrivate()
{
    foreach (QtPulseAudioSinkPort* port, ports)
        delete port;
}

void QtPulseAudioSinkPrivate::onSinkInfo(
        pa_context* context, const pa_sink_info* sinkInfo, int eol, void* userData)
{
    Q_UNUSED(context);

    if (!eol)
    {
        auto d = reinterpret_cast< QtPulseAudioSinkPrivate* >(userData);

        QWriteLocker locker(&d->lock);

        if (sinkInfo->active_port && d->activePort &&
                d->activePort->name() != QString::fromUtf8(sinkInfo->active_port->name))
        {
            d->activePort = d->portsByName.value(
                                QString::fromUtf8(sinkInfo->active_port->name), NULL);

            emit d->q_func()->activePortChanged(d->activePort? d->activePort->name(): QString());
        }
    }
}
