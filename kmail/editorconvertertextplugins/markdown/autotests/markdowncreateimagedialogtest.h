/*
    SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MARKDOWNCREATEIMAGEDIALOGTEST_H
#define MARKDOWNCREATEIMAGEDIALOGTEST_H

#include <QObject>

class MarkdownCreateImageDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownCreateImageDialogTest(QObject *parent = nullptr);
    ~MarkdownCreateImageDialogTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // MARKDOWNCREATEIMAGEDIALOGTEST_H
