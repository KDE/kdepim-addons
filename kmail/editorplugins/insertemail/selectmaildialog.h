/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

class SelectMailWidget;
class SelectMailDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectMailDialog(QWidget *parent = nullptr);
    ~SelectMailDialog() override;

    Q_REQUIRED_RESULT QStringList selectedEmails() const;

    void accept() override;
Q_SIGNALS:
    void emailSelected(const QStringList &lst);

private:
    void writeConfig();
    void readConfig();
    void slotInsertEmails();
    SelectMailWidget *const mSelectMailWidget;
};
