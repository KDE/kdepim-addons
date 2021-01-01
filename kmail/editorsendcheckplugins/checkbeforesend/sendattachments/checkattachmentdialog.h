/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKATTACHMENTDIALOG_H
#define CHECKATTACHMENTDIALOG_H

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
    QListWidget *mListWidget = nullptr;
};

#endif // CHECKATTACHMENTDIALOG_H
