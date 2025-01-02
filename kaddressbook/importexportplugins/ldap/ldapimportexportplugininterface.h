/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KAddressBookImportExport/PluginInterface>

class LDapImportExportPluginInterface : public KAddressBookImportExport::PluginInterface
{
    Q_OBJECT
public:
    explicit LDapImportExportPluginInterface(QObject *parent = nullptr);
    ~LDapImportExportPluginInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

private:
    void slotImportLdap();
    void importLdap();
};
