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

#ifndef QTPULSEAUDIOSOURCEPRIVATE_H
#define QTPULSEAUDIOSOURCEPRIVATE_H

#include <QtGlobal>
#include <QString>

#include <pulse/context.h>
#include <pulse/introspect.h>

#include <qtpulseaudio/qtpulseaudiosource.h>

#include "qtpulseaudiodata.h"
#include "qtpulseaudiofacilityprivate.h"

class QtPulseAudioSourcePrivate : public QtPulseAudioFacilityPrivate
{
    Q_DECLARE_PUBLIC(QtPulseAudioSource)

private:
    static void onSourceInfo(
            pa_context* context, const pa_source_info* sourceInfo, int eol, void* userData);

private:
    QtPulseAudioSourcePrivate(const QtPulseAudioData& pulseAudioData);
    ~QtPulseAudioSourcePrivate();

private:
    quint32 index;
    QString name;
};

#endif // QTPULSEAUDIOSOURCEPRIVATE_H
