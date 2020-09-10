/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LDIFIMPORTEXPORTPLUGININTERFACE_H
#define LDIFIMPORTEXPORTPLUGININTERFACE_H

#include <KAddressBookImportExport/PluginInterface>

class LDifImportExportPluginInterface : public KAddressBookImportExport::PluginInterface
{
    Q_OBJECT
public:
    explicit LDifImportExportPluginInterface(QObject *parent = nullptr);
    ~LDifImportExportPluginInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
    Q_REQUIRED_RESULT bool canImportFileType(const QUrl &url) override;
    void importFile(const QUrl &url) override;
private:
    void slotImportLdif();
    void slotExportLdif();
    void importLdif();
    void exportLdif();
    void importLdifFile(const QString &fileName);
};

#endif // LDIFIMPORTEXPORTPLUGININTERFACE_H
