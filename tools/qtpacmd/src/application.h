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

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QCoreApplication>

#include <qtpulseaudio/qtpulseaudio.h>

class QtPulseAudioConnection;

class Application : public QCoreApplication
{
    Q_OBJECT

public:
    Application(int& argc, char* argv[]);
    virtual ~Application();

private slots:
    void onConnected();

private:
    QScopedPointer< QtPulseAudioConnection > pulseAudio;
};

#endif // APPLICATION_H
