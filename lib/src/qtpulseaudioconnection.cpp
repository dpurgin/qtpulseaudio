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

#include <qtpulseaudio/qtpulseaudioconnnection.h>

#include <qtpulseaudio/qtpulseaudiocard.h>
#include <qtpulseaudio/qtpulseaudiostream.h>

#include <pulse/error.h>
#include <pulse/context.h>
#include <pulse/introspect.h>
#include <pulse/thread-mainloop.h>

#include <QCoreApplication>
#include <QMutex>
#include <QMutexLocker>
#include <QHash>
#include <QStringBuilder>

#include <QWaitCondition>

#include "qtpulseaudioconnectionprivate.h"
#include "qtpulseaudiodata.h"

QtPulseAudioConnection::QtPulseAudioConnection(QtPulseAudio::Facilities facilities, QObject* parent)
    : QObject(parent),
      d(new QtPulseAudioConnectionPrivate(this))
{
    d->facilities = facilities;

    d->pulseAudioData.mainLoop = pa_threaded_mainloop_new();
    d->pulseAudioData.mainLoopApi = pa_threaded_mainloop_get_api(d->pulseAudioData.mainLoop);

    pa_threaded_mainloop_start(d->pulseAudioData.mainLoop);
}

QtPulseAudioConnection::~QtPulseAudioConnection()
{
    if (d->pulseAudioData.mainLoop)
    {
        //TODO: check cleanup code for PulseAudio
        pa_threaded_mainloop_stop(d->pulseAudioData.mainLoop);
        pa_threaded_mainloop_free(d->pulseAudioData.mainLoop);
    }
}

QtPulseAudioCard* QtPulseAudioConnection::cardByIndex(quint32 index) const
{
    return d->cardsByIndex.value(index, NULL);
}

QtPulseAudioCard* QtPulseAudioConnection::cardByName(const QString& name) const
{
    return d->cardsByName.value(name, NULL);
}

bool QtPulseAudioConnection::connectToServer(const QString& server)
{
    bool result = false;

    if (state() == QtPulseAudio::Unconnected ||
            state() == QtPulseAudio::Failed)
    {
        d->pulseAudioData.context = pa_context_new(d->pulseAudioData.mainLoopApi,
                                                      qApp->applicationName().toUtf8().data());

        pa_context_set_state_callback(d->pulseAudioData.context,
                                      &QtPulseAudioConnectionPrivate::onContextNotify,
                                      d);

        int ret = pa_context_connect(d->pulseAudioData.context,
                                     server.isEmpty()? NULL: server.toUtf8().data(),
                                     PA_CONTEXT_NOFLAGS,
                                     NULL);

        if (ret < 0)
            emit error(QString::fromUtf8(pa_strerror(ret)));
        else
            result = true;
    }
    else
        emit error(QLatin1String("Context is already connected or in process of connection"));

    return result;
}

QtPulseAudioStream* QtPulseAudioConnection::createStream(QtPulseAudio::StreamType streamType,
                                                      const QString& name)
{
    QString streamName = name;

    if (streamName.isEmpty())
    {
        streamName = qApp->applicationName()
                % QLatin1String("_Stream")
                % QString::number(d->streamsByName.size());
    }
    else
    {
        int idx = 0;

        while (d->streamsByName.contains(streamName))
            streamName = name % QString::number(idx++);
    }

//    QtPulseAudioStream* stream = new QtPulseAudioStream(d->pulseAudioData,
//                                                        streamType,
//                                                        streamName);

//    d->streamsByName.insert(streamName, stream);

//    return stream;
    return NULL;
}

QtPulseAudioSink* QtPulseAudioConnection::sinkByIndex(quint32 index) const
{
    return d->sinksByIndex.value(index, NULL);
}

QtPulseAudioSink* QtPulseAudioConnection::sinkByName(const QString& name) const
{
    return d->sinksByName.value(name, NULL);
}

QtPulseAudio::ConnectionState QtPulseAudioConnection::state() const
{
    return d->state;
}