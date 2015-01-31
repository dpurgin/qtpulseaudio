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

#ifndef QTPULSEAUDIOCARDPROFILE_H
#define QTPULSEAUDIOCARDPROFILE_H

#include <QtGlobal>

#include <pulse/version.h>

#if PA_CHECK_VERSION(5, 0, 0)
#include <qtpulseaudio/qtpulseaudio.h>
#endif

class QtPulseAudioCardProfilePrivate;
class QtPulseAudioData;

class QtPulseAudioCardProfile
{
    Q_DISABLE_COPY(QtPulseAudioCardProfile)

    friend class QtPulseAudioCardPrivate;

private:
    explicit QtPulseAudioCardProfile(const QtPulseAudioData& data);
    ~QtPulseAudioCardProfile();

public:
#if PA_CHECK_VERSION(5, 0, 0)
    bool available() const;
#endif
    QString description() const;
    QString name() const;
    quint32 priority() const;
    quint32 sinks() const;
    quint32 sources() const;

private:
    QtPulseAudioCardProfilePrivate* const d;
};

#endif // QTPULSEAUDIOCARDPROFILE_H
