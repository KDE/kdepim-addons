/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "akonadidatasetools_private_export.h"
#include <QWidget>
class QPlainTextEdit;
class AKONADIDATASETOOLS_TESTS_EXPORT AkonadiDatabaseToolsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AkonadiDatabaseToolsWidget(QWidget *parent = nullptr);
    ~AkonadiDatabaseToolsWidget() override;

    void appendText(const QString &text);

private:
    QPlainTextEdit *const mPlainTextEdit;
};
