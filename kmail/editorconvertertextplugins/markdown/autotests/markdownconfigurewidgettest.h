/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNCONFIGUREWIDGETTEST_H
#define MARKDOWNCONFIGUREWIDGETTEST_H

#include <QObject>

class MarkdownConfigureWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownConfigureWidgetTest(QObject *parent = nullptr);
    ~MarkdownConfigureWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // MARKDOWNCONFIGUREWIDGETTEST_H
