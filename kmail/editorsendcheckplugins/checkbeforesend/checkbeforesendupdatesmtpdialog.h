/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CHECKBEFORESENDUPDATESMTPDIALOG_H
#define CHECKBEFORESENDUPDATESMTPDIALOG_H

#include <QDialog>
class QCheckBox;
class CheckBeforeSendUpdateSmtpDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CheckBeforeSendUpdateSmtpDialog(QWidget *parent = nullptr);
    ~CheckBeforeSendUpdateSmtpDialog() override;

    Q_REQUIRED_RESULT bool changeSmtp() const;

private:
    QCheckBox *mChangeSmtp = nullptr;
};

#endif // CHECKBEFORESENDUPDATESMTPDIALOG_H
