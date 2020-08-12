/*
   SPDX-FileCopyrightText: 2018 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
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
    QHash<QString, Grantlee::Filter *> filters(const QString &name) override;
};

#endif
