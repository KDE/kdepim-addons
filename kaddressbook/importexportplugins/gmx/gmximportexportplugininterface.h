/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GMXIMPORTEXPORTPLUGININTERFACE_H
#define GMXIMPORTEXPORTPLUGININTERFACE_H

#include <KAddressBookImportExport/KAddressBookImportExportPluginInterface>
#include <QFile>
#include <KContacts/Addressee>

class GMXImportExportPluginInterface : public KAddressBookImportExport::KAddressBookImportExportPluginInterface
{
    Q_OBJECT
public:
    explicit GMXImportExportPluginInterface(QObject *parent = nullptr);
    ~GMXImportExportPluginInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
    Q_REQUIRED_RESULT bool canImportFileType(const QUrl &url) override;
private:
    void doExport(QFile *fp, const KContacts::AddresseeList &list) const;
    void slotImportGmx();
    void slotExportGmx();
    void importGMX();
    void exportGMX();
};

#endif // GMXIMPORTEXPORTPLUGININTERFACE_H
