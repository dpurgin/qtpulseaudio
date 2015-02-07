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

#include "qtpulseaudiofacilityfactory.h"

#include <qtpulseaudio/qtpulseaudiofacility.h>

#include <QMutex>
#include <QMutexLocker>

QtPulseAudioFacilityFactory* QtPulseAudioFacilityFactory::mInstance = NULL;

QtPulseAudioFacilityFactory::QtPulseAudioFacilityFactory()
{
}

QtPulseAudioFacilityFactory::~QtPulseAudioFacilityFactory()
{
}

QtPulseAudioFacilityFactory* QtPulseAudioFacilityFactory::instance()
{
    if (mInstance == NULL)
    {
        QMutex mutex;

        QMutexLocker locker(&mutex);

        if (mInstance == NULL)
            mInstance = new QtPulseAudioFacilityFactory();
    }

    return mInstance;
}

QSharedPointer< QtPulseAudioFacility > QtPulseAudioFacilityFactory::create(
        QtPulseAudio::Facility facility, const QtPulseAudioData& data)
{
    QSharedPointer< QtPulseAudioFacility > result;
    FactoryMethod method = mFactoryMethods.value(facility, NULL);

    if (method)
        result = (*method)(data);

    return result;
}

void QtPulseAudioFacilityFactory::registerFacility(
        QtPulseAudio::Facility facility, FactoryMethod method)
{
    mFactoryMethods.insert(facility, method);
}
