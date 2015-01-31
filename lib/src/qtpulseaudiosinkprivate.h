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
#include <QHash>
#include <QSet>
#include <QString>

#include <pulse/introspect.h>

#include <qtpulseaudio/qtpulseaudiosink.h>
#include <qtpulseaudio/qtpulseaudiosinkport.h>

#include "qtpulseaudiofacilityprivate.h"

class QtPulseAudioSinkPrivate : protected QtPulseAudioFacilityPrivate
{
    Q_DECLARE_PUBLIC(QtPulseAudioSink)

private:
    static void onSinkInfo(
            pa_context* context, const pa_sink_info* sinkInfo, int eol, void* userData);

private:
    QtPulseAudioSinkPrivate(const QtPulseAudioData& pulseAudioData);
    ~QtPulseAudioSinkPrivate();

private:

    quint32 index;
    QString name;

    QtPulseAudioSinkPort* activePort;

    QSet< QtPulseAudioSinkPort* > ports;
    QHash< QString, QtPulseAudioSinkPort* > portsByName;
};

#endif // QTPULSEAUDIOSINKPRIVATE_H
