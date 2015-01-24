# This file is part of QtPulseAudio Tools & Examples.
# Copyright (C) 2015  Dmitriy Purgin <dpurgin@gmail.com>
#
# This is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# QtPulseAudio Tools & Examples are distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with QtPulseAudio Tools & Examples.  If not, see <http://www.gnu.org/licenses/>.

TEMPLATE = app
TARGET = qtpacmd

CONFIG += console

LIBS += -L../../lib -lqtpulseaudio

INCLUDEPATH += ../../lib/include

QT -= gui
QT += core

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    src/application.h

SOURCES += \
    src/application.cpp \
    src/main.cpp
