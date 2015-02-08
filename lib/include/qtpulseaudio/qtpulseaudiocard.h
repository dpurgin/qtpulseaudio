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

#ifndef QTPULSEAUDIOCARD_H
#define QTPULSEAUDIOCARD_H

#include <QObject>
#include <QSharedPointer>

#include <qtpulseaudio/qtpulseaudiofacility.h>

class QtPulseAudioCardPrivate;
class QtPulseAudioCardProfile;
class QtPulseAudioData;

class QtPulseAudioCard : public QtPulseAudioFacility
{
    Q_OBJECT
    Q_DISABLE_COPY(QtPulseAudioCard)

    friend void registerCardFacility();

    static QSharedPointer< QtPulseAudioFacility > create(const QtPulseAudioData& pulseAudioData);

public:
    void update();

    QtPulseAudioCardProfile* activeProfile();
    void setActiveProfile(const QString& activeProfile);

//    QString driver() const;
    quint32 index();
    QString name();
//    quint32 ownerModule() const;

//    void update(const pa_card_info* paCardInfo);

signals:
    void activeProfileChanged(const QString& profileName);
//    void activeProfileChanged(const PulseAudioCardProfile* activeProfile);
//    void driverChanged(const QString& driver);
//    void nameChanged(const QString& name);
//    void ownerModuleChanged(quint32 ownerModule);
//    void propertiesChanged();

public slots:

private:
    explicit QtPulseAudioCard(const QtPulseAudioData& pulseAudioData);
    virtual ~QtPulseAudioCard();

private:
    Q_DECLARE_PRIVATE(QtPulseAudioCard)
};

#endif // QTPULSEAUDIOCARD_H
