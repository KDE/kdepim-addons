/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KAddressBookImportExport/PluginInterface>

class LDifImportExportPluginInterface : public KAddressBookImportExport::PluginInterface
{
    Q_OBJECT
public:
    explicit LDifImportExportPluginInterface(QObject *parent = nullptr);
    ~LDifImportExportPluginInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
    [[nodiscard]] bool canImportFileType(const QUrl &url) override;
    void importFile(const QUrl &url) override;

private:
    void slotImportLdif();
    void slotExportLdif();
    void importLdif();
    void exportLdif();
    void importLdifFile(const QString &fileName);
};
