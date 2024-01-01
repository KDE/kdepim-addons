/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QLineEdit>
namespace KSieveCore
{
class SieveImapAccountSettings;
}

class SelectImapLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit SelectImapLineEdit(QWidget *parent = nullptr);
    ~SelectImapLineEdit() override;

    void setSieveImapAccountSettings(const KSieveCore::SieveImapAccountSettings &account);

private:
    QCompleter *mCompleter = nullptr;
};
