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

#ifndef QTPULSEAUDIOSINKPRIVATE_H
#define QTPULSEAUDIOSINKPRIVATE_H

#include <QtGlobal>
#include <QDebug>
#include <QString>

#include <pulse/introspect.h>

class QtPulseAudioSinkPrivate
{
    friend class QtPulseAudioFacilityFactory;
    friend class QtPulseAudioSink;

private:
    QtPulseAudioSinkPrivate(const pa_sink_info* sinkInfo);
    ~QtPulseAudioSinkPrivate();

private:
    quint32 index;
    QString name;
};

#endif // QTPULSEAUDIOSINKPRIVATE_H
