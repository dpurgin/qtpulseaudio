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

#ifndef QTPULSEAUDIOCARDPRIVATE_H
#define QTPULSEAUDIOCARDPRIVATE_H

#include <QString>

#include <pulse/introspect.h>

#include "qtpulseaudiofacilityprivate.h"

class QtPulseAudioCardPrivate : protected QtPulseAudioFacilityPrivate
{
    Q_DISABLE_COPY(QtPulseAudioCardPrivate)

    friend class QtPulseAudioCard;

private:
    explicit QtPulseAudioCardPrivate(const QtPulseAudioData& pulseAudioData);
    ~QtPulseAudioCardPrivate();

private:
//    PulseAudioCardProfile* activeProfile;
//    QString driver;
    quint32 index;
    QString name;
//    quint32 ownerModule;
//    QSet< PulseAudioCardProfile* > profiles;  // this one owns the pointers
//    QHash< QString, PulseAudioCardProfile* > profilesByName;
//    QHash< QString, QVariant> properties;
};

#endif // QTPULSEAUDIOCARDPRIVATE_H
