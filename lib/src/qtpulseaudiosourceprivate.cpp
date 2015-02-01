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

#include "qtpulseaudiosourceprivate.h"

QtPulseAudioSourcePrivate::QtPulseAudioSourcePrivate(const QtPulseAudioData& pulseAudioData)
    : QtPulseAudioFacilityPrivate(pulseAudioData)
{
    const pa_source_info* sourceInfo =
            reinterpret_cast< const pa_source_info* >(pulseAudioData.data);

    index = sourceInfo->index;
    name = QString::fromUtf8(sourceInfo->name);
}

QtPulseAudioSourcePrivate::~QtPulseAudioSourcePrivate()
{
}

void QtPulseAudioSourcePrivate::onSourceInfo(
        pa_context* context, const pa_source_info* sourceInfo, int eol, void* userData)
{
}
