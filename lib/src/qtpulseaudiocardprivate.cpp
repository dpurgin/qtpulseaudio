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

#include "qtpulseaudiocardprivate.h"

#include <qtpulseaudio/qtpulseaudiocardprofile.h>

#include <pulse/version.h>

QtPulseAudioCardPrivate::QtPulseAudioCardPrivate(const QtPulseAudioData& pulseAudioData)
    : QtPulseAudioFacilityPrivate(pulseAudioData)
{
    const pa_card_info* cardInfo = reinterpret_cast< const pa_card_info* >(pulseAudioData.data);

    index = cardInfo->index;
    name = QString::fromUtf8(cardInfo->name);

    for (quint32 i = 0; i < cardInfo->n_profiles; i++)
    {
#if PA_CHECK_VERSION(5, 0, 0)
        QtPulseAudioCardProfile* profile =
                new QtPulseAudioCardProfile(QtPulseAudioData(NULL, cardInfo->profiles2[i]));
#else
        QtPulseAudioCardProfile* profile =
                new QtPulseAudioCardProfile(QtPulseAudioData(NULL, &cardInfo->profiles[i]));
#endif

        profiles.insert(profile);
        profilesByName.insert(profile->name(), profile);
    }
}

QtPulseAudioCardPrivate::~QtPulseAudioCardPrivate()
{
    foreach (QtPulseAudioCardProfile* profile, profiles)
        delete profile;
}

void QtPulseAudioCardPrivate::onCardInfo(
        pa_context *context, const pa_card_info *cardInfo, int eol, void *userData)
{
    Q_UNUSED(context);

    if (!eol)
    {
        QtPulseAudioCardPrivate* d = reinterpret_cast< QtPulseAudioCardPrivate* >(userData);

#if PA_CHECK_VERSION(5, 0, 0)
        if (cardInfo->active_profile2 && d->activeProfile &&
                QString::fromUtf8(cardInfo->active_profile2->name) != d->activeProfile->name())
        {
            d->activeProfile = d->profilesByName.value(
                                   QString::fromUtf8(cardInfo->active_profile2->name), NULL);

            emit d->q_func()->activeProfileChanged(
                        d->activeProfile? d->activeProfile->name(): QString());
        }
#else
        if (cardInfo->active_profile && d->activeProfile &&
                QString::fromUtf8(cardInfo->active_profile->name) != d->activeProfile->name())
        {
            d->activeProfile = d->profilesByName.value(
                                   QString::fromUtf8(cardInfo->active_profile->name));
        }
#endif
    }
}

