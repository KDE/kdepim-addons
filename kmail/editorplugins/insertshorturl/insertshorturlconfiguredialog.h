/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
class InsertShorturlConfigureWidget;
class InsertShorturlConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InsertShorturlConfigureDialog(QWidget *parent = nullptr);
    ~InsertShorturlConfigureDialog() override;

    void accept() override;

private:
    InsertShorturlConfigureWidget *const mInsertShortUrlWidget;
};
