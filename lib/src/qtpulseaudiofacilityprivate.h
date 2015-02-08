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

#ifndef QTPULSEAUDIOFACILITYPRIVATE_H
#define QTPULSEAUDIOFACILITYPRIVATE_H

#include <QReadWriteLock>

#include <pulse/context.h>

#include "qtpulseaudiodata.h"

class QtPulseAudioFacility;

class QtPulseAudioFacilityPrivate
{
    friend class QtPulseAudioFacility;

protected:
    explicit QtPulseAudioFacilityPrivate(const QtPulseAudioData& pulseAudioData)
        : context(pulseAudioData.context),
          q_ptr(NULL)
    {
    }
    virtual ~QtPulseAudioFacilityPrivate()
    {
    }

    static void trivialCallback(pa_context* context, int success, void* userData)
    {
        Q_UNUSED(context)
        Q_UNUSED(success)
        Q_UNUSED(userData)
    }

protected:
    pa_context* context;

    QtPulseAudioFacility* q_ptr;

    QReadWriteLock lock;
};

#endif // QTPULSEAUDIOFACILITYPRIVATE_H
