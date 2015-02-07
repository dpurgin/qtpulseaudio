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

#include <QMap>
#include <QSharedPointer>

#define qtpaFacilityFactory (QtPulseAudioFacilityFactory::instance())

class QtPulseAudioData;
class QtPulseAudioFacility;

class QtPulseAudioFacilityFactory
{
    typedef QSharedPointer< QtPulseAudioFacility > (*FactoryMethod)(const QtPulseAudioData& data);
    typedef QMap< QtPulseAudio::Facility, FactoryMethod > FactoryMethods;

public:
    static QtPulseAudioFacilityFactory* instance();

    QSharedPointer< QtPulseAudioFacility > create(
            QtPulseAudio::Facility facility, const QtPulseAudioData& data);

    void registerFacility(QtPulseAudio::Facility facility, FactoryMethod method);

private:
    explicit QtPulseAudioFacilityFactory();
    ~QtPulseAudioFacilityFactory();

    static QtPulseAudioFacilityFactory* mInstance;

    FactoryMethods mFactoryMethods;
};

#endif // QTPULSEAUDIOFACILITYFACTORY_H
