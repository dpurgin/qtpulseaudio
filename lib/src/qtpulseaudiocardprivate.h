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

#include <QHash>
#include <QSet>
#include <QString>

#include <qtpulseaudio/qtpulseaudiocard.h>

#include "qtpulseaudiofacilityprivate.h"

class QtPulseAudioCardProfile;
struct pa_card_info;

class QtPulseAudioCardPrivate : public QtPulseAudioFacilityPrivate
{
protected:
    explicit QtPulseAudioCardPrivate(const QtPulseAudioData& pulseAudioData);
    virtual ~QtPulseAudioCardPrivate();

private:
    Q_DISABLE_COPY(QtPulseAudioCardPrivate)
    Q_DECLARE_PUBLIC(QtPulseAudioCard)

    static void onCardInfo(
            pa_context* context, const pa_card_info* cardInfo, int eol, void* userData);

private:
    QtPulseAudioCardProfile* activeProfile;
//    QString driver;
    quint32 index;
    QString name;
//    quint32 ownerModule;

    QSet< QtPulseAudioCardProfile* > profiles;
    QHash< QString, QtPulseAudioCardProfile* > profilesByName;
//    QHash< QString, QVariant> properties;
};

#endif // QTPULSEAUDIOCARDPRIVATE_H
