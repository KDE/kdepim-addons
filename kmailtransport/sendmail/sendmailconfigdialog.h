/*
    SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MAILTRANSPORT_SENDMAILCONFIGDIALOG_H
#define MAILTRANSPORT_SENDMAILCONFIGDIALOG_H

#include <QDialog>
namespace MailTransport {
class Transport;
class SendmailConfigWidget;
}
class SendMailConfigDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SendMailConfigDialog(MailTransport::Transport *transport, QWidget *parent = nullptr);
    ~SendMailConfigDialog() override;

private:
    void okClicked();
    void slotTextChanged(const QString &text);
    void slotEnabledOkButton(bool);

    MailTransport::Transport *mTransport = nullptr;
    MailTransport::SendmailConfigWidget *mConfigWidget = nullptr;
    QPushButton *mOkButton = nullptr;
};

#endif
