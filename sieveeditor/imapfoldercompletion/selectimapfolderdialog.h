/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPFOLDERDIALOG_H
#define SELECTIMAPFOLDERDIALOG_H

#include <QDialog>
namespace KSieveUi {
class SieveImapAccountSettings;
}
class SelectImapFolderWidget;
class SelectImapFolderDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectImapFolderDialog(const KSieveUi::SieveImapAccountSettings &account, QWidget *parent = nullptr);
    ~SelectImapFolderDialog();

    QString selectedFolderName() const;

private:
    void slotEnabledNewFolder(bool enabled);
    void writeConfig();
    void readConfig();
    void slotCreateFolder();

    SelectImapFolderWidget *mSelectImapFolderWidget = nullptr;
    QPushButton *mNewFolder = nullptr;
};

#endif // SELECTIMAPFOLDERDIALOG_H
