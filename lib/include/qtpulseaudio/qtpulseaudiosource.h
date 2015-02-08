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

#ifndef QTPULSEAUDIOSOURCE_H
#define QTPULSEAUDIOSOURCE_H

#include <qtpulseaudio/qtpulseaudioconfig.h>
#include <qtpulseaudio/qtpulseaudiofacility.h>

class QtPulseAudioData;
class QtPulseAudioSourcePrivate;

class QTPULSEAUDIO_DECL QtPulseAudioSource : public QtPulseAudioFacility
{
    Q_OBJECT
    Q_DISABLE_COPY(QtPulseAudioSource)

    friend void registerSourceFacility();

    static QSharedPointer< QtPulseAudioFacility > create(const QtPulseAudioData& data);

public:
    void update();

    quint32 index();
    QString name();

signals:

public slots:

private:
    explicit QtPulseAudioSource(const QtPulseAudioData& data);
    virtual ~QtPulseAudioSource();

private:
    Q_DECLARE_PRIVATE(QtPulseAudioSource)
};

#endif // QTPULSEAUDIOSOURCE_H
