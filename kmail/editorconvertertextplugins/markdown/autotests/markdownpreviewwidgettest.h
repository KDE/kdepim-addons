/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNPREVIEWWIDGETTEST_H
#define MARKDOWNPREVIEWWIDGETTEST_H

#include <QObject>

class MarkdownPreviewWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownPreviewWidgetTest(QObject *parent = nullptr);
    ~MarkdownPreviewWidgetTest() = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};

#endif // MARKDOWNPREVIEWWIDGETTEST_H
