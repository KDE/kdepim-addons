/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef WINDOWSCONTACTIMPORTEXPORTPLUGININTERFACE_H
#define WINDOWSCONTACTIMPORTEXPORTPLUGININTERFACE_H

#include <KAddressBookImportExport/PluginInterface>
#include <KContacts/Addressee>

class WindowsContactImportExportPluginInterface : public KAddressBookImportExport::PluginInterface
{
    Q_OBJECT
public:
    explicit WindowsContactImportExportPluginInterface(QObject *parent = nullptr);
    ~WindowsContactImportExportPluginInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

    Q_REQUIRED_RESULT bool canImportFileType(const QUrl &url) override;
    void importFile(const QUrl &url) override;

private:
    void slotExportWindowsContact();
    void slotImportWindowsContact();
    void importWindowsContact();
    void exportWindowsContact();
};

#endif
