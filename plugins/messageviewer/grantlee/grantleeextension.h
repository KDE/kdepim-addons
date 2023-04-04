/*
   SPDX-FileCopyrightText: 2018 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include <KTextTemplate/Filter>
#include <KTextTemplate/TagLibraryInterface>
#include <QObject>

class AddressFormatter : public KTextTemplate::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
    bool isSafe() const override;
};

class DateFormatter : public KTextTemplate::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

class DateTimeFormatter : public KTextTemplate::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

class TimeFormatter : public KTextTemplate::Filter
{
public:
    QVariant doFilter(const QVariant &input, const QVariant &arg, bool autoescape) const override;
};

class TagLibrary : public QObject, public KTextTemplate::TagLibraryInterface
{
    Q_OBJECT
    Q_INTERFACES(KTextTemplate::TagLibraryInterface)
    Q_PLUGIN_METADATA(IID "org.grantlee.TagLibraryInterface")
public:
    explicit TagLibrary(QObject *parent = nullptr);
    QHash<QString, KTextTemplate::Filter *> filters(const QString &name) override;
};
