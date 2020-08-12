/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MAILMERGEDIALOG_H
#define MAILMERGEDIALOG_H
#include <QDialog>
namespace MailMerge {
class MailMergeWidget;
class MailMergeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MailMergeDialog(QWidget *parent = nullptr);
    ~MailMergeDialog();
private:
    MailMergeWidget *mMailMergeWidget = nullptr;
};
}

#endif // MAILMERGEDIALOG_H
