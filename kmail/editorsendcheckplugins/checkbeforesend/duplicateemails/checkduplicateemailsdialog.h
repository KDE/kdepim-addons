/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

class QListWidget;
class CheckDuplicateEmailsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CheckDuplicateEmailsDialog(QWidget *parent = nullptr);
    ~CheckDuplicateEmailsDialog() override;

    void setDuplicatedEmails(const QMap<QString, int> &emails);

private:
    void readConfig();
    void writeConfig();
    QListWidget *const mListWidget;
};
