/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
namespace KSieveCore
{
class SieveImapAccountSettings;
}
class SelectImapFolderWidget;
class SelectImapFolderDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectImapFolderDialog(const KSieveCore::SieveImapAccountSettings &account, QWidget *parent = nullptr);
    ~SelectImapFolderDialog() override;

    [[nodiscard]] QString selectedFolderName() const;

private:
    void slotEnabledNewFolder(bool enabled);
    void writeConfig();
    void readConfig();
    void slotCreateFolder();

    SelectImapFolderWidget *const mSelectImapFolderWidget;
    QPushButton *const mNewFolder;
};
