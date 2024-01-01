/*
    SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MarkdownCreateImageWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownCreateImageWidgetTest(QObject *parent = nullptr);
    ~MarkdownCreateImageWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValue();
    void shouldGenerateLink();
    void shouldChangeState();
    void shouldAddSize();
    void shouldEmitSignal();
};
