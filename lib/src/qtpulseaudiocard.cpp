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

#include <qtpulseaudio/qtpulseaudiocard.h>

#include "qtpulseaudiodata.h"

//#include "pulseaudiocardprofile.h"

#include <QDebug>
//#include <QHash>
//#include <QSet>
//#include <QThread>
//#include <QVariant>

//#include <pulse/context.h>
#include <pulse/introspect.h>
//#include <pulse/version.h>

#include "qtpulseaudiocardprivate.h"


QtPulseAudioCard::QtPulseAudioCard(QtPulseAudioCardPrivate* const dptr)
    : QtPulseAudioFacility(),
      d(dptr)
{
    qDebug() << "Discovered card:" << d->index << d->name;
}

QtPulseAudioCard::~QtPulseAudioCard()
{
    qDebug() << "Destroying card:" << d->index << d->name;

    delete d;
}

//PulseAudioCard::PulseAudioCard(pa_context* context, const pa_card_info* paCardInfo, QObject *parent)
//    : QObject(parent),
//      d(new PulseAudioCardPrivate)
//{
//    qDebug() << QThread::currentThread() << "Discovered card: " << paCardInfo->name << ", index: " << paCardInfo->index;

//    d->context = context;

//    d->index = paCardInfo->index;
//    d->name = QString::fromUtf8(paCardInfo->name);
//    d->ownerModule = paCardInfo->owner_module;
//    d->driver = QString::fromUtf8(paCardInfo->driver);

//    for (quint32 i = 0; i < paCardInfo->n_profiles; i++)
//    {
//#if PA_CHECK_VERSION(5, 0, 0)
//        PulseAudioCardProfile* profile = new PulseAudioCardProfile(paCardInfo->profiles2[i]);
//#else
//        PulseAudioCardProfile* profile = new PulseAudioCardProfile(&paCardInfo->profiles[i]);
//#endif

//        d->profiles.insert(profile);
//        d->profilesByName.insert(profile->name(), profile);
//    }

//    d->activeProfile = d->profilesByName.value(paCardInfo->active_profile->name);
//}

//PulseAudioCard::~PulseAudioCard()
//{
//    qDeleteAll(d->profiles);
//}

//PulseAudioCardProfile* PulseAudioCard::activeProfile() const
//{
//    return d->activeProfile;
//}

//QString PulseAudioCard::driver() const
//{
//    return d->driver;
//}

quint32 QtPulseAudioCard::index() const
{
    return d->index;
}

QString QtPulseAudioCard::name() const
{
    return d->name;
}

//quint32 PulseAudioCard::ownerModule() const
//{
//    return d->ownerModule;
//}

//void PulseAudioCard::update(const pa_card_info* paCardInfo)
//{
//    QSet< QString > emitters;

//    if (d->name != QLatin1String(paCardInfo->name))
//    {
//        d->name = QLatin1String(paCardInfo->name);
//        emitters.insert(QLatin1String("name"));
//    }

//    if (d->ownerModule != paCardInfo->owner_module)
//    {
//        d->ownerModule = paCardInfo->owner_module;
//        emitters.insert(QLatin1String("ownerModule"));
//    }

//    if (d->driver != QLatin1String(paCardInfo->driver))
//    {
//        d->driver = QLatin1String(paCardInfo->driver);
//        emitters.insert(QLatin1String("driver"));
//    }

//    // for now, assume that profiles can never be added/removed/changed at runtime

//    if (d->activeProfile->name() != QString::fromUtf8(paCardInfo->active_profile->name))
//    {
//        d->activeProfile = d->profilesByName.value(paCardInfo->active_profile->name, NULL);
//        emitters.insert(QLatin1String("activeProfile"));
//    }

//    if (emitters.size() > 0)
//    {
//        emit propertiesChanged();

//        foreach (QString emitter, emitters)
//        {
//            if (emitter == QLatin1String("name"))
//                emit nameChanged(d->name);
//            else if (emitter == QLatin1String("ownerModule"))
//                emit ownerModuleChanged(d->ownerModule);
//            else if (emitter == QLatin1String("driver"))
//                emit driverChanged(d->driver);
//            else if (emitter == QLatin1String("activeProfile"))
//                emit activeProfileChanged(d->activeProfile);
//        }
//    }

//}

//void PulseAudioCard::setActiveProfile(const QString& profileName)
//{
//    if (d->activeProfile && profileName == d->activeProfile->name())
//        return;

//    pa_operation_unref(pa_context_set_card_profile_by_index(d->context,
//                                                            index(),
//                                                            profileName.toUtf8().data(),
//                                                            &PulseAudioCardPrivate::trivialCallback,
//                                                            NULL));
//}
