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

#ifndef QTPULSEAUDIODATA_H
#define QTPULSEAUDIODATA_H

#include <pulse/context.h>
#include <pulse/mainloop-api.h>
#include <pulse/thread-mainloop.h>

#include <QtGlobal>

class QtPulseAudioData
{
public:
    explicit QtPulseAudioData():
        context(NULL),
        mainLoopApi(NULL),
        mainLoop(NULL)
    {
    }

    explicit QtPulseAudioData(const QtPulseAudioData& other)
        : context(NULL),
          mainLoopApi(NULL),
          mainLoop(NULL)
    {
        assign(other);
    }

    pa_context* context;
    pa_mainloop_api* mainLoopApi;
    pa_threaded_mainloop* mainLoop;

private:
    void assign(const QtPulseAudioData& other)
    {
        context = other.context;
        mainLoopApi = other.mainLoopApi;
        mainLoop = other.mainLoop;
    }
};

#endif // QTPULSEAUDIODATA_H
