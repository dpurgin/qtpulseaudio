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

#ifndef QTPULSEAUDIOFACILITYFACTORY_H
#define QTPULSEAUDIOFACILITYFACTORY_H

#include <qtpulseaudio/qtpulseaudio.h>
#include <qtpulseaudio/qtpulseaudiocard.h>
#include <qtpulseaudio/qtpulseaudiofacility.h>
#include <qtpulseaudio/qtpulseaudiosink.h>

#include "qtpulseaudiocardprivate.h"
#include "qtpulseaudiosinkprivate.h"

class QtPulseAudioFacilityFactory
{
public:
    static QtPulseAudioFacility* create(
            QtPulseAudio::Facility facility,
            pa_context* pulseAudioContext,
            const void* pulseAudioData)
    {
        QtPulseAudioFacility* result = NULL;

        if (facility == QtPulseAudio::Sink)
        {
            result = new QtPulseAudioSink(
                        new QtPulseAudioSinkPrivate(
                            pulseAudioContext,
                            reinterpret_cast< const pa_sink_info* >(pulseAudioData)));
        }
        else if (facility == QtPulseAudio::Card)
        {
            result = new QtPulseAudioCard(
                        new QtPulseAudioCardPrivate(
                            pulseAudioContext,
                            reinterpret_cast< const pa_card_info* >(pulseAudioData)));
        }

        return result;
    }
};

#endif // QTPULSEAUDIOFACILITYFACTORY_H
