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

#include "qtpulseaudioserverprivate.h"

#include <QWriteLocker>

#include <pulse/introspect.h>

#ifdef QTPULSEAUDIOSERVER_DEBUG
#include <QDebug>
#endif // QTPULSEAUDIOSERVER_DEBUG

QtPulseAudioServerPrivate::QtPulseAudioServerPrivate(const QtPulseAudioData& pulseAudioData)
    : QtPulseAudioFacilityPrivate(pulseAudioData)
{
#ifdef QTPULSEAUDIOSERVER_DEBUG
    qDebug();
#endif // QTPULSEAUDIOSERVER_DEBUG

    const pa_server_info* serverInfo =
            reinterpret_cast< const pa_server_info* >(pulseAudioData.data);

#ifdef QTPULSEAUDIOSERVER_DEBUG
    qDebug() << "serverInfo->default_sink_name = "
             << QString::fromUtf8(serverInfo->default_sink_name);
    qDebug() << "serverInfo->default_source_name = "
             << QString::fromUtf8(serverInfo->default_source_name);
#endif // QTPULSEAUDIOSERVER_DEBUG

    userName = QString::fromUtf8(serverInfo->user_name);
    hostName = QString::fromUtf8(serverInfo->host_name);
    serverVersion = QString::fromUtf8(serverInfo->server_version);
    serverName = QString::fromUtf8(serverInfo->server_name);
    defaultSinkName = QString::fromUtf8(serverInfo->default_sink_name);
    defaultSourceName = QString::fromUtf8(serverInfo->default_source_name);
    cookie = serverInfo->cookie;
}

QtPulseAudioServerPrivate::~QtPulseAudioServerPrivate()
{
#ifdef QTPULSEAUDIOSERVER_DEBUG
    qDebug();
#endif // QTPULSEAUDIOSERVER_DEBUG
}

void QtPulseAudioServerPrivate::onServerInfo(
        pa_context *context, const pa_server_info *serverInfo, void *userData)
{
#ifdef QTPULSEAUDIOSERVER_DEBUG
    qDebug();
#endif // QTPULSEAUDIOSERVER_DEBUG

    Q_UNUSED(context);

    QtPulseAudioServerPrivate* d = reinterpret_cast< QtPulseAudioServerPrivate* >(userData);

    QWriteLocker locker(&d->lock);

#ifdef QTPULSEAUDIOSERVER_DEBUG
    qDebug() << "serverInfo->default_sink_name = "
             << QString::fromUtf8(serverInfo->default_sink_name)
             << ", d->defaultSinkName = "
             << d->defaultSinkName;
    qDebug() << "serverInfo->default_source_name = "
             << QString::fromUtf8(serverInfo->default_source_name)
             << ", d->defaultSourceName = "
             << d->defaultSourceName;
#endif // QTPULSEAUDIOSERVER_DEBUG

    if (QString::fromUtf8(serverInfo->default_sink_name) != d->defaultSinkName)
    {
        d->defaultSinkName = QString::fromUtf8(serverInfo->default_sink_name);

        emit d->q_func()->defaultSinkChanged(d->defaultSinkName);
    }

    if (QString::fromUtf8(serverInfo->default_source_name) != d->defaultSourceName)
    {
        d->defaultSourceName = QString::fromUtf8(serverInfo->default_source_name);

        emit d->q_func()->defaultSourceChanged(d->defaultSourceName);
    }
}
