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

#include <qtpulseaudio/qtpulseaudiocardprofile.h>

#include "qtpulseaudiodata.h"

#include <pulse/introspect.h>
#include <pulse/version.h>

class QtPulseAudioCardProfilePrivate
{
    friend class QtPulseAudioCardProfile;

    explicit QtPulseAudioCardProfilePrivate(const QtPulseAudioData& pulseAudioData)
        : sinks(0),
          sources(0),
          priority(0)
#if PA_CHECK_VERSION(5, 0, 0)
        , available(false)
#endif
    {
#if PA_CHECK_VERSION(5, 0, 0)
        const pa_card_profile_info2* profileInfo =
                reinterpret_cast< const pa_card_profile_info2* >(pulseAudioData.data);
#else
        const pa_card_profile_info* profileInfo =
                reinterpret_cast< const pa_card_profile* >(pulseAudioData.data);
#endif
        name = QString::fromUtf8(profileInfo->name);
        description = QString::fromUtf8(profileInfo->description);

        sinks = profileInfo->n_sinks;
        sources = profileInfo->n_sources;
        priority = profileInfo->priority;

#if PA_CHECK_VERSION(5, 0, 0)
        available = (profileInfo->available != 0);
#endif
    }

    QString name;
    QString description;

    quint32 sinks;
    quint32 sources;
    quint32 priority;

#if PA_CHECK_VERSION(5, 0, 0)
    bool available;
#endif
};

QtPulseAudioCardProfile::QtPulseAudioCardProfile(const QtPulseAudioData& data)
    : d(new QtPulseAudioCardProfilePrivate(data))
{
    qDebug() << "Discovered profile:" << d->name;
}

QtPulseAudioCardProfile::~QtPulseAudioCardProfile()
{
    delete d;
}

#if PA_CHECK_VERSION(5, 0, 0)
bool QtPulseAudioCardProfile::available() const
{
    return d->available;
}
#endif

QString QtPulseAudioCardProfile::description() const
{
    return d->description;
}

QString QtPulseAudioCardProfile::name() const
{
    return d->name;
}

quint32 QtPulseAudioCardProfile::priority() const
{
    return d->priority;
}

quint32 QtPulseAudioCardProfile::sinks() const
{
    return d->sinks;
}

quint32 QtPulseAudioCardProfile::sources() const
{
    return d->sources;
}
