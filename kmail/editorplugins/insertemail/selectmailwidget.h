/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTMAILWIDGET_H
#define SELECTMAILWIDGET_H

#include <QWidget>
namespace Akonadi
{
class EmailAddressSelectionWidget;
}

class SelectMailWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SelectMailWidget(QWidget *parent = nullptr);
    ~SelectMailWidget() override;

    Q_REQUIRED_RESULT QStringList selectedEmails() const;

private:
    Akonadi::EmailAddressSelectionWidget *mView = nullptr;
};

#endif // SELECTMAILWIDGET_H
