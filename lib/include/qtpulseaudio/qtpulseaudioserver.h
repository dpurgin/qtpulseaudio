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

#ifndef QTPULSEAUDIOSERVER_H
#define QTPULSEAUDIOSERVER_H

#include <qtpulseaudio/qtpulseaudiofacility.h>

class QtPulseAudioServerPrivate;

class QtPulseAudioServer : public QtPulseAudioFacility
{
    Q_OBJECT
    Q_DISABLE_COPY(QtPulseAudioServer)

    friend void registerServerFacility();

    static QSharedPointer< QtPulseAudioFacility > create(const QtPulseAudioData& data);

public:
    void update();

    QString userName();
    QString hostName();
    QString serverName();
    QString serverVersion();

    QString defaultSink();
    void setDefaultSink(const QString& defaultSink);

    QString defaultSource();
    void setDefaultSource(const QString& defaultSource);

    quint32 cookie();

signals:
    void defaultSinkChanged(const QString& defaultSink);
    void defaultSourceChanged(const QString& defaultSource);

private:
    explicit QtPulseAudioServer(const QtPulseAudioData& data);
    ~QtPulseAudioServer();

private:
    Q_DECLARE_PRIVATE(QtPulseAudioServer)
};

#endif // QTPULSEAUDIOSERVER_H

