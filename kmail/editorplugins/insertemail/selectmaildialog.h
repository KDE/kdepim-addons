/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTMAILDIALOG_H
#define SELECTMAILDIALOG_H

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
    SelectMailWidget *mSelectMailWidget = nullptr;
};

#endif // SELECTMAILDIALOG_H
