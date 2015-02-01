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


#include <qtpulseaudio/qtpulseaudiosource.h>

#include <QDebug>

#include "qtpulseaudiofacilityfactory.h"

#include "qtpulseaudiosourceprivate.h"

void registerSourceFacility()
{
    qtpaFacilityFactory->registerFacility(QtPulseAudio::Source, &QtPulseAudioSource::create);
}

Q_CONSTRUCTOR_FUNCTION(registerSourceFacility)

QtPulseAudioSource::QtPulseAudioSource(const QtPulseAudioData& data)
    : QtPulseAudioFacility(new QtPulseAudioSourcePrivate(data), this)
{
    qDebug() << "Discovered source:" << index() << name();
}

QtPulseAudioSource::~QtPulseAudioSource()
{
}

QtPulseAudioFacility* QtPulseAudioSource::create(const QtPulseAudioData& data)
{
    return new QtPulseAudioSource(data);
}

quint32 QtPulseAudioSource::index() const
{
    const Q_D(QtPulseAudioSource);

    return d->index;
}

QString QtPulseAudioSource::name() const
{
    const Q_D(QtPulseAudioSource);

    return d->name;
}

void QtPulseAudioSource::update()
{
    Q_D(QtPulseAudioSource);

    pa_operation_unref(
        pa_context_get_source_info_by_index(
            d->context, d->index, &QtPulseAudioSourcePrivate::onSourceInfo, d));
}
