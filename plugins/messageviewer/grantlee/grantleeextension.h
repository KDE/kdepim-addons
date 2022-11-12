/*
   SPDX-FileCopyrightText: 2018 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include <QObject>
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#include <grantlee/filter.h>
#include <grantlee/taglibraryinterface.h>
#else
#include <KTextTemplate/Filter>
#include <KTextTemplate/TagLibraryInterface>
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class AddressFormatter : public Grantlee::Filter
#else
class AddressFormatter : public KTextTemplate::Filter
#endif
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
    bool isSafe() const override;
};

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class DateFormatter : public Grantlee::Filter
#else
class DateFormatter : public KTextTemplate::Filter
#endif
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class DateTimeFormatter : public Grantlee::Filter
#else
class DateTimeFormatter : public KTextTemplate::Filter
#endif
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class TimeFormatter : public Grantlee::Filter
#else
class TimeFormatter : public KTextTemplate::Filter
#endif
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
class TagLibrary : public QObject, public Grantlee::TagLibraryInterface
#else
class TagLibrary : public QObject, public KTextTemplate::TagLibraryInterface
#endif
{
    Q_OBJECT
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    Q_INTERFACES(Grantlee::TagLibraryInterface)
#else
    Q_INTERFACES(KTextTemplate::TagLibraryInterface)
#endif
    Q_PLUGIN_METADATA(IID "org.grantlee.TagLibraryInterface")
public:
    explicit TagLibrary(QObject *parent = nullptr);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QHash<QString, Grantlee::Filter *> filters(const QString &name) override;
#else
    QHash<QString, KTextTemplate::Filter *> filters(const QString &name) override;
#endif
};
