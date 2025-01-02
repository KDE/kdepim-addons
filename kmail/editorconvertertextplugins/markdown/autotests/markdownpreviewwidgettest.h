/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MarkdownPreviewWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownPreviewWidgetTest(QObject *parent = nullptr);
    ~MarkdownPreviewWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
};
