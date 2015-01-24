# This file is part of QtPulseAudio.
# Copyright (C) 2015  Dmitriy Purgin <dpurgin@gmail.com>
#
# QtPulseAudio is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# QtPulseAudio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU General Public License and
# GNU Lesser General Public License along with QtPulseAudio. If not, see
# <http://www.gnu.org/licenses/>.


TEMPLATE = lib

TARGET = qtpulseaudio
VERSION = 0.1

CONFIG += link_pkgconfig

PKGCONFIG += libpulse

DEFINES += QTPULSEAUDIO

INCLUDEPATH += include

QT -= gui
QT += core

SOURCES += \
    src/qtpulseaudio.cpp \
    src/qtpulseaudiocard.cpp \
    src/qtpulseaudiodata.cpp \
    src/qtpulseaudiostream.cpp \
    src/qtpulseaudioconnection.cpp \
    src/qtpulseaudioconnectionprivate.cpp \
    src/qtpulseaudiosink.cpp \
    src/qtpulseaudiofacilityfactory.cpp \
    src/qtpulseaudiofacility.cpp \
    src/qtpulseaudiosinkprivate.cpp \
    src/qtpulseaudiocardprivate.cpp

HEADERS += \
    src/qtpulseaudiodata.h \
    include/qtpulseaudio/qtpulseaudio.h \
    include/qtpulseaudio/qtpulseaudiocard.h \
    include/qtpulseaudio/qtpulseaudioconfig.h \
    include/qtpulseaudio/qtpulseaudiostream.h \
    include/qtpulseaudio/qtpulseaudioconnnection.h \
    include/qtpulseaudio/qtpulseaudiosink.h \
    src/qtpulseaudioconnectionprivate.h \
    src/qtpulseaudiofacilityfactory.h \
    include/qtpulseaudio/qtpulseaudiofacility.h \
    src/qtpulseaudiosinkprivate.h \
    src/qtpulseaudiocardprivate.h

