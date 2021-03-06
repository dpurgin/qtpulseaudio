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

#include <qtpulseaudio/qtpulseaudio.h>

#include <QFileInfo>
#include <QMutex>
#include <QMutexLocker>
#include <QStringBuilder>
#include <QThread>

#include <iostream>

void qtpaMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    Q_UNUSED(type)

    static QMutex mutex;
    QMutexLocker locker(&mutex);

    QString threadId = QLatin1String("[0x") %
            QString::number(
                (ptrdiff_t)QThread::currentThread(), 16).rightJustified(PTRDIFF_WIDTH / 8, QLatin1Char('0')) %
            QLatin1Char(']');

    QString sourceFile(QFileInfo(context.file).fileName() %
                       QLatin1Char(':') %
                       QString::number(context.line));

    std::cerr << threadId.toUtf8().data() << ": "
              << sourceFile.toUtf8().data() << ": "
              << context.function << ": "
              << msg.toUtf8().data()
              << "\n";
}

namespace {
    static void initialize()
    {
        qRegisterMetaType< QtPulseAudio::ConnectionState >();
        qRegisterMetaType< QtPulseAudio::PortAvailability >();
        qRegisterMetaType< QtPulseAudio::StreamType >();       
    }

    Q_CONSTRUCTOR_FUNCTION(initialize)
}

namespace QtPulseAudio {
    void installMessageHandler()
    {
        qInstallMessageHandler(qtpaMessageHandler);
    }
}

QDebug operator<<(QDebug dbg, QtPulseAudio::ConnectionState state)
{
    QByteArray str;

    switch (state)
    {
        case QtPulseAudio::Unconnected:
            str.append("Unconnected");
            break;

        case QtPulseAudio::Connecting:
            str.append("Connecting");
            break;

        case QtPulseAudio::Connected:
            str.append("Connected");
            break;

        case QtPulseAudio::Failed:
            str.append("Failed");
            break;

        default:
            str.append("Unknown");
            break;
    }

    dbg.nospace() << "QtPulseAudio::ConnectionState(" << str << ")";

    return dbg.space();
}

QDebug operator<<(QDebug dbg, QtPulseAudio::PortAvailability portAvailability)
{
    QByteArray str;

    switch (portAvailability)
    {
        case QtPulseAudio::PortAvailable:
            str.append("Available");
            break;

        case QtPulseAudio::PortNotAvailable:
            str.append("NotAvailable");
            break;

        case QtPulseAudio::PortUnknown:
            str.append("Unknown");
            break;
    }

    dbg.nospace() << "QtPulseAudio::PortAvailability(" << str << ")";

    return dbg.space();
}

QDebug operator<<(QDebug dbg, QtPulseAudio::StreamType streamType)
{
    QByteArray str;

    switch (streamType)
    {
    case QtPulseAudio::Playback:
        str.append("Playback");
        break;

    case QtPulseAudio::Record:
        str.append("Record");
        break;

    default:
        str.append("Unknown");
    }

    dbg.nospace() << "QtPulseAudio::StreamType(" << str;

    return dbg.space();
}
