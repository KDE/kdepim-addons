/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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

    [[nodiscard]] QStringList selectedEmails() const;

Q_SIGNALS:
    void doubleClicked();

private:
    Akonadi::EmailAddressSelectionWidget *mView = nullptr;
};
