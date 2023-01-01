/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
class QListWidget;
class CheckAttachmentDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CheckAttachmentDialog(QWidget *parent = nullptr);
    ~CheckAttachmentDialog() override;

    void setEmails(const QStringList &emails);

private:
    void writeConfig();
    void readConfig();
    QListWidget *const mListWidget;
};
