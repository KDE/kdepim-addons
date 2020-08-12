/*
    SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MARKDOWNCREATELINKWIDGETTEST_H
#define MARKDOWNCREATELINKWIDGETTEST_H

#include <QObject>

class MarkdownCreateLinkWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownCreateLinkWidgetTest(QObject *parent = nullptr);
    ~MarkdownCreateLinkWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldGenerateLink();
    void shouldEmitSignal();
};

#endif // MARKDOWNCREATELINKWIDGETTEST_H
