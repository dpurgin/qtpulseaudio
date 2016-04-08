/*
 * This file is part of QtPulseAudio Tools & Examples.
 * Copyright (C) 2015  Dmitriy Purgin <dpurgin@gmail.com>
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QtPulseAudio Tools & Examples are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QtPulseAudio Tools & Examples.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "application.h"

#include <qtpulseaudio/qtpulseaudioconnection.h>
#include <qtpulseaudio/qtpulseaudiosink.h>

#include <QDebug>

Application::Application(int& argc, char* argv[])
    : QCoreApplication(argc, argv)
{
    pulseAudio.reset(new QtPulseAudioConnection(QtPulseAudio::AllFacilities));

    connect(pulseAudio.data(), &QtPulseAudioConnection::connected,
            this, &Application::onConnected);

    qDebug() << "connect(): " << pulseAudio->connectToServer();
}

Application::~Application()
{

}

void Application::onConnected()
{
    qDebug();

    QSharedPointer< QtPulseAudioSink > sink = pulseAudio->sinkByIndex(0);

    if (sink)
        qDebug() << "sink:" << sink->name();
}
