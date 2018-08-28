/*
   Copyright (c) 2018 Volker Krause <vkrause@kde.org>

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published by
   the Free Software Foundation; either version 2 of the License, or (at your
   option) any later version.

   This library is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
   License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to the
   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

#include "grantleeextension.h"

#include <KItinerary/Place>
#include <KContacts/Address>

#include <grantlee/exception.h>
#include <grantlee/parser.h>

#include <QDateTime>
#include <QDebug>
#include <QTimeZone>

QVariant AddressFormatter::doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const
{
    Q_UNUSED(arg);
    Q_UNUSED(autoescape);

    if (!KItinerary::JsonLd::isA<KItinerary::PostalAddress>(input)) {
        return {};
    }
    const auto a = input.value<KItinerary::PostalAddress>();

    KContacts::Address address;
    address.setStreet(a.streetAddress());
    address.setPostalCode(a.postalCode());
    address.setLocality(a.addressLocality());
    address.setRegion(a.addressRegion());
    address.setCountry(KContacts::Address::ISOtoCountry(a.addressCountry()));

    auto s = escape(address.formattedAddress().trimmed().replace(QLatin1String("\n\n"), QLatin1String("\n")));
    return s.get().replace(QLatin1Char('\n'), QLatin1String("<br/>"));
}

bool AddressFormatter::isSafe() const
{
    return true;
}

QVariant DateFormatter::doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const
{
    Q_UNUSED(arg);
    Q_UNUSED(autoescape);

    const auto dt = input.value<QDateTime>();
    if (!dt.isValid()) {
        return {};
    }

    return QLocale().toString(dt.date(), QLocale::ShortFormat);
}

QVariant DateTimeFormatter::doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const
{
    Q_UNUSED(arg);
    Q_UNUSED(autoescape);

    const auto dt = input.value<QDateTime>();
    if (!dt.isValid()) {
        return {};
    }

    auto s = QLocale().toString(dt, QLocale::ShortFormat);
    if (dt.timeSpec() == Qt::TimeZone || dt.timeSpec() == Qt::OffsetFromUTC || dt.timeSpec() == Qt::UTC) {
        s += QLatin1Char(' ') + dt.timeZone().abbreviation(dt);
    }
    return s;
}

QVariant TimeFormatter::doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const
{
    Q_UNUSED(arg);
    Q_UNUSED(autoescape);

    const auto dt = input.value<QDateTime>();
    if (!dt.isValid()) {
        return {};
    }

    auto s = QLocale().toString(dt.time(), QLocale::ShortFormat);
    if (dt.timeSpec() == Qt::TimeZone || dt.timeSpec() == Qt::OffsetFromUTC || dt.timeSpec() == Qt::UTC) {
        s += QLatin1Char(' ') + dt.timeZone().abbreviation(dt);
    }
    return s;
}


TagLibrary::TagLibrary(QObject *parent)
    : QObject(parent)
{
}

QHash<QString, Grantlee::Filter*> TagLibrary::filters(const QString &name)
{
    Q_UNUSED(name);
    QHash<QString, Grantlee::Filter*> filters;
    filters.insert(QStringLiteral("formatAddress"), new AddressFormatter());
    filters.insert(QStringLiteral("formatDate"), new DateFormatter());
    filters.insert(QStringLiteral("formatDateTime"), new DateTimeFormatter());
    filters.insert(QStringLiteral("formatTime"), new TimeFormatter());
    return filters;
}
