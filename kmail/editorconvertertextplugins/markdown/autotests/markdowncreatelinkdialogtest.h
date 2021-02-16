/*
    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MARKDOWNCREATELINKDIALOGTEST_H
#define MARKDOWNCREATELINKDIALOGTEST_H

#include <QObject>

class MarkdownCreateLinkDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownCreateLinkDialogTest(QObject *parent = nullptr);
    ~MarkdownCreateLinkDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // MARKDOWNCREATELINKDIALOGTEST_H
