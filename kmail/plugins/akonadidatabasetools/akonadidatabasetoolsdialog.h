/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "akonadidatasetools_private_export.h"
#include <QDialog>
class AkonadiDatabaseToolsWidget;
class AKONADIDATASETOOLS_TESTS_EXPORT AkonadiDatabaseToolsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AkonadiDatabaseToolsDialog(QWidget *parent = nullptr);
    ~AkonadiDatabaseToolsDialog() override;

    void appendText(const QString &text);
    void appendErrorText(const QString &text);

private:
    void writeConfig();
    void readConfig();
    AkonadiDatabaseToolsWidget *const mAkonadiDatabaseToolsWidget;
};
