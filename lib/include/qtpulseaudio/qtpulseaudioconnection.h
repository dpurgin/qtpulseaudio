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

#ifndef QTPULSEAUDIOCONNECTION_H
#define QTPULSEAUDIOCONNECTION_H

#include <QObject>

#include <qtpulseaudio/qtpulseaudioconfig.h>
#include <qtpulseaudio/qtpulseaudio.h>

class QtPulseAudioCard;
class QtPulseAudioSink;
class QtPulseAudioStream;

class QTPULSEAUDIO_DECL QtPulseAudioConnection : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QtPulseAudioConnection)

public:
    QtPulseAudioConnection(QtPulseAudio::Facilities facilities, QObject* parent = NULL);
    virtual ~QtPulseAudioConnection();

    QtPulseAudioStream* createStream(QtPulseAudio::StreamType streamType,
                                     const QString& name = QString());

    QtPulseAudioCard* cardByIndex(quint32 index) const;
    QtPulseAudioCard* cardByName(const QString& name) const;

    bool connectToServer(const QString& server = QString());

    QtPulseAudioSink* sinkByIndex(quint32 index) const;
    QtPulseAudioSink* sinkByName(const QString& name) const;

    QtPulseAudio::ConnectionState state() const;

signals:
    void cardAdded(int index);
    void cardRemoved(int index);

    void sinkAdded(int index);
    void sinkRemoved(int index);

    void error(QString errorText);
    void failed();
    void connecting();
    void connected();
    void stateChanged(QtPulseAudio::ConnectionState state);

private:        
    class QtPulseAudioConnectionPrivate;
    QtPulseAudioConnectionPrivate* d;
};

#endif // QTPULSEAUDIOCONNECTION_H

