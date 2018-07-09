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

#ifndef KITINERARY_GRANTLEEEXTENSION_H
#define KITINERARY_GRANTLEEEXTENSION_H

#include <grantlee/filter.h>
#include <grantlee/taglibraryinterface.h>

#include <QObject>

class AddressFormatter : public Grantlee::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
    bool isSafe() const override;
};

class DateFormatter : public Grantlee::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

class DateTimeFormatter : public Grantlee::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

class TimeFormatter : public Grantlee::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

class TagLibrary : public QObject, public Grantlee::TagLibraryInterface
{
    Q_OBJECT
    Q_INTERFACES(Grantlee::TagLibraryInterface)
    Q_PLUGIN_METADATA(IID "org.grantlee.TagLibraryInterface")
public:
    explicit TagLibrary(QObject *parent = nullptr);
    QHash<QString, Grantlee::Filter*> filters(const QString &name) override;
};

#endif
