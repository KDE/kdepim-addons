/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class ExternalComposerPluginEditorTest : public QObject
{
    Q_OBJECT
public:
    explicit ExternalComposerPluginEditorTest(QObject *parent = nullptr);
    ~ExternalComposerPluginEditorTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValue();
};
