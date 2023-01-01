/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KAddressBookImportExport/PluginInterface>
#include <KContacts/Addressee>
class QFile;

class GMXImportExportPluginInterface : public KAddressBookImportExport::PluginInterface
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
