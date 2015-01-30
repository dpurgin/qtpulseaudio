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

#ifndef QTPULSEAUDIOSINK_H
#define QTPULSEAUDIOSINK_H

#include <QObject>

#include <qtpulseaudio/qtpulseaudiofacility.h>

//class PulseAudioSinkPort;

class QtPulseAudioSinkPrivate;

class QtPulseAudioSink : public QtPulseAudioFacility
{
    Q_OBJECT
    Q_DISABLE_COPY(QtPulseAudioSink)

    friend void registerSinkFacility();

    static QtPulseAudioFacility* create(const QtPulseAudioData& data);

public:
    void update();

//    PulseAudioSinkPort* activePort() const;
//    void setActivePort(const QString& port);

    quint32 index() const;
    QString name() const;

//    void update(const pa_sink_info* sinkInfo);

//signals:
//    void activePortChanged(const PulseAudioSinkPort* activePort);

//public slots:

private:
    explicit QtPulseAudioSink(const QtPulseAudioData& data);
    virtual ~QtPulseAudioSink();

private:
    Q_DECLARE_PRIVATE(QtPulseAudioSink)
};

#endif // QTPULSEAUDIOSINK_H
