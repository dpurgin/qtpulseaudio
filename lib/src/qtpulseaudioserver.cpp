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

#include <qtpulseaudio/qtpulseaudioserver.h>

#include <QReadLocker>

#include <pulse/introspect.h>

#include "qtpulseaudiofacilityfactory.h"
#include "qtpulseaudioserverprivate.h"

void registerServerFacility()
{
    qtpaFacilityFactory->registerFacility(QtPulseAudio::Server, &QtPulseAudioServer::create);
}

Q_CONSTRUCTOR_FUNCTION(registerServerFacility)

QtPulseAudioServer::QtPulseAudioServer(const QtPulseAudioData &data)
    : QtPulseAudioFacility(new QtPulseAudioServerPrivate(data), this)
{
    qDebug() << "Discovered server:" << serverName();
}

QtPulseAudioServer::~QtPulseAudioServer()
{

}

quint32 QtPulseAudioServer::cookie()
{
    Q_D(QtPulseAudioServer);

    QReadLocker locker(&d->lock);

    return d->cookie;
}

QSharedPointer< QtPulseAudioFacility > QtPulseAudioServer::create(const QtPulseAudioData &data)
{
    return QSharedPointer< QtPulseAudioFacility >(new QtPulseAudioServer(data));
}

QString QtPulseAudioServer::defaultSink()
{
    Q_D(QtPulseAudioServer);

    QReadLocker locker(&d->lock);

    return d->defaultSinkName;
}

QString QtPulseAudioServer::defaultSource()
{
    Q_D(QtPulseAudioServer);

    QReadLocker locker(&d->lock);

    return d->defaultSourceName;
}

QString QtPulseAudioServer::hostName()
{
    Q_D(QtPulseAudioServer);

    QReadLocker locker(&d->lock);

    return d->hostName;
}

QString QtPulseAudioServer::serverName()
{
    Q_D(QtPulseAudioServer);

    QReadLocker locker(&d->lock);

    return d->serverName;
}

QString QtPulseAudioServer::serverVersion()
{
    Q_D(QtPulseAudioServer);

    QReadLocker locker(&d->lock);

    return d->serverVersion;
}

void QtPulseAudioServer::setDefaultSink(const QString& defaultSink)
{
#ifdef QTPULSEAUDIOSERVER_DEBUG
    qDebug() << defaultSink;
#endif // QTPULSEAUDIOSERVER_DEBUG

    Q_D(QtPulseAudioServer);

    QReadLocker locker(&d->lock);

    if (defaultSink != d->defaultSinkName)
    {
        pa_operation_unref(
            pa_context_set_default_sink(
                d->context,
                defaultSink.toUtf8().data(),
                &QtPulseAudioFacilityPrivate::trivialCallback,
                NULL));
    }
}

void QtPulseAudioServer::setDefaultSource(const QString& defaultSource)
{
#ifdef QTPULSEAUDIOSERVER_DEBUG
    qDebug() << defaultSource;
#endif // QTPULSEAUDIOSERVER_DEBUG

    Q_D(QtPulseAudioServer);

    QReadLocker locker(&d->lock);

    if (defaultSource != d->defaultSourceName)
    {
        pa_operation_unref(
            pa_context_set_default_source(
                d->context,
                defaultSource.toUtf8().data(),
                &QtPulseAudioFacilityPrivate::trivialCallback,
                NULL));
    }
}

void QtPulseAudioServer::update()
{
#ifdef QTPULSEAUDIOSERVER_DEBUG
    qDebug();
#endif // QTPULSEAUDIOSERVER_DEBUG

    Q_D(QtPulseAudioServer);

    pa_operation_unref(
        pa_context_get_server_info(
            d->context, &QtPulseAudioServerPrivate::onServerInfo, d));
}

QString QtPulseAudioServer::userName()
{
    Q_D(QtPulseAudioServer);

    QReadLocker locker(&d->lock);

    return d->userName;
}
