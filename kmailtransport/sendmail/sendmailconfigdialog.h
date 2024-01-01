/*
    SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QDialog>
namespace MailTransport
{
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

    MailTransport::Transport *const mTransport;
    MailTransport::SendmailConfigWidget *const mConfigWidget;
    QPushButton *mOkButton = nullptr;
};
