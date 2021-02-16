/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNPREVIEWDIALOGTEST_H
#define MARKDOWNPREVIEWDIALOGTEST_H

#include <QObject>

class MarkdownPreviewDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownPreviewDialogTest(QObject *parent = nullptr);
    ~MarkdownPreviewDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // MARKDOWNPREVIEWDIALOGTEST_H
