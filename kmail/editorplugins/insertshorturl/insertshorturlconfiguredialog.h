/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef INSERTSHORTURLCONFIGUREDIALOG_H
#define INSERTSHORTURLCONFIGUREDIALOG_H

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

#endif // INSERTSHORTURLCONFIGUREDIALOG_H
