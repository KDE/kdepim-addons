/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KAddressBookImportExport/PluginInterface>
#include <KContacts/Addressee>
class QFile;
class CSVImportExportPluginInterface : public KAddressBookImportExport::PluginInterface
{
    Q_OBJECT
public:
    explicit CSVImportExportPluginInterface(QObject *parent = nullptr);
    ~CSVImportExportPluginInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

    [[nodiscard]] bool canImportFileType(const QUrl &url) override;
    void importFile(const QUrl &url) override;

private:
    void exportCSV();
    void slotImportCVS();
    void slotExportCVS();
    void exportToFile(QFile *file, const KContacts::Addressee::List &contacts) const;
    void importCSV();
};
