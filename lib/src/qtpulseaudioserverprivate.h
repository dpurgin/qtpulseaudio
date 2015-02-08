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

#ifndef QTPULSEAUDIOSERVERPRIVATE_H
#define QTPULSEAUDIOSERVERPRIVATE_H

#include <qtpulseaudio/qtpulseaudioserver.h>

#include "qtpulseaudiofacilityprivate.h"

class QtPulseAudioData;
struct pa_server_info;

class QtPulseAudioServerPrivate : public QtPulseAudioFacilityPrivate
{
    Q_DISABLE_COPY(QtPulseAudioServerPrivate)
    Q_DECLARE_PUBLIC(QtPulseAudioServer)

private:
    static void onServerInfo(
            pa_context* context, const pa_server_info* serverInfo, void* userData);

private:
    QtPulseAudioServerPrivate(const QtPulseAudioData& data);
    ~QtPulseAudioServerPrivate();

private:
    QString userName;
    QString hostName;
    QString serverVersion;
    QString serverName;
    QString defaultSinkName;
    QString defaultSourceName;
    quint32 cookie;
};

#endif // QTPULSEAUDIOSERVERPRIVATE_H
