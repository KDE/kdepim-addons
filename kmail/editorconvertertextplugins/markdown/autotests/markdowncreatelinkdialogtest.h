/*
    SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

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
