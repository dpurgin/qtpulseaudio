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
#include <qtpulseaudio/qtpulseaudiofacility.h>

#include "qtpulseaudiodata.h"

class QtPulseAudioFacilityFactory
{
public:
    typedef QtPulseAudioFacility* (*FactoryMethod)(const QtPulseAudioData& data);

    static QtPulseAudioFacility* create(
            QtPulseAudio::Facility facility, const QtPulseAudioData& data)
    {
        QtPulseAudioFacility* result = NULL;
        FactoryMethod method = mFactoryMethods.value(facility, NULL);

        if (method)
            result = (*method)(data);

        return result;
    }

    static void registerType(QtPulseAudio::Facility facility, FactoryMethod method)
    {
        mFactoryMethods.insert(facility, method);
    }

private:
    static QMap< QtPulseAudio::Facility, FactoryMethod > mFactoryMethods;
};

#endif // QTPULSEAUDIOFACILITYFACTORY_H
