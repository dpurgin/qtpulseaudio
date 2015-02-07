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

#include <qtpulseaudio/qtpulseaudiosink.h>

#include <pulse/introspect.h>

#include <QDebug>

#include "qtpulseaudiofacilityfactory.h"

#include "qtpulseaudiosinkprivate.h"

void registerSinkFacility()
{
    qtpaFacilityFactory->registerFacility(QtPulseAudio::Sink, &QtPulseAudioSink::create);
}

Q_CONSTRUCTOR_FUNCTION(registerSinkFacility)

QtPulseAudioSink::QtPulseAudioSink(const QtPulseAudioData& data)
    : QtPulseAudioFacility(new QtPulseAudioSinkPrivate(data), this)
{
    qDebug() << "Discovered sink:" << index() << name();
}

QtPulseAudioSink::~QtPulseAudioSink()
{
}

QSharedPointer< QtPulseAudioFacility > QtPulseAudioSink::create(const QtPulseAudioData &data)
{
    return QSharedPointer< QtPulseAudioSink >(new QtPulseAudioSink(data),
                                              &QtPulseAudioFacility::deleterMethod);
}

void QtPulseAudioSink::update()
{
    Q_D(QtPulseAudioSink);

    pa_operation_unref(
        pa_context_get_sink_info_by_index(
            d->context, d->index, &QtPulseAudioSinkPrivate::onSinkInfo, d));
}

//#include <QDebug>
//#include <QHash>
//#include <QSet>
//#include <QThread>
//#include <QVector>

//#include <pulse/context.h>
//#include <pulse/introspect.h>

//#include "pulseaudiosinkport.h"

//class PulseAudioSink::PulseAudioSinkPrivate
//{
//    friend class PulseAudioSink;

//    PulseAudioSinkPrivate(): activePort(NULL), context(NULL) {}

//    static void trivialCallback(pa_context*, int, void*)
//    {
//    }

//    pa_context* context;

//    QString name;
//    quint32 index;

//    PulseAudioSinkPort* activePort;

//    QSet< PulseAudioSinkPort* > sinkPorts;
//    QHash< QString, PulseAudioSinkPort* > sinkPortsByName;
//};

//PulseAudioSink::PulseAudioSink(pa_context* context, const pa_sink_info* sinkInfo, QObject *parent)
//    : QObject(parent),
//      d(new PulseAudioSinkPrivate())
//{
//    qDebug() << QThread::currentThread() << "Discovered sink: " << sinkInfo->name << ", index: " << sinkInfo->index;

//    d->context = context;

//    d->name = QString::fromUtf8(sinkInfo->name);
//    d->index = sinkInfo->index;

//    for (quint32 c = 0; c < sinkInfo->n_ports; c++)
//    {
//        PulseAudioSinkPort* sinkPort = new PulseAudioSinkPort(sinkInfo->ports[c]);

//        d->sinkPorts.insert(sinkPort);
//        d->sinkPortsByName.insert(sinkPort->name(), sinkPort);
//    }

//    if (sinkInfo->active_port)
//        d->activePort = d->sinkPortsByName.value(QString::fromUtf8(sinkInfo->active_port->name), NULL);
//}

//PulseAudioSink::~PulseAudioSink()
//{
//    qDeleteAll(d->sinkPorts);

//    delete d;
//}

//PulseAudioSinkPort* PulseAudioSink::activePort() const
//{
//    return d->activePort;
//}

quint32 QtPulseAudioSink::index() const
{
    const Q_D(QtPulseAudioSink);

    return d->index;
}

QString QtPulseAudioSink::name() const
{
    const Q_D(QtPulseAudioSink);

    return d->name;
}

//void PulseAudioSink::setActivePort(const QString& port)
//{
//    qDebug() << QThread::currentThread();

//    if (d->activePort && d->activePort->name() != port)
//    {
//        pa_operation_unref(pa_context_set_sink_port_by_index(d->context,
//                                                             d->index,
//                                                             port.toUtf8().data(),
//                                                             &PulseAudioSinkPrivate::trivialCallback,
//                                                             NULL));
//    }
//}

//void PulseAudioSink::update(const pa_sink_info* sinkInfo)
//{
//    QSet< QString > emitters;

//    if (sinkInfo->active_port && d->activePort &&
//            d->activePort->name() != QString::fromUtf8(sinkInfo->active_port->name))
//    {
//        d->activePort = d->sinkPortsByName.value(sinkInfo->active_port->name, NULL);

//        if (!d->activePort)
//            qWarning() << "Port is active but was not discovered:" << sinkInfo->active_port->name;

//        emitters.insert("activePort");
//    }

//    foreach (QString emitter, emitters)
//    {
//        if (emitter == QLatin1String("activePort"))
//            emit activePortChanged(d->activePort);
//    }
//}
