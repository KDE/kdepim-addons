/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KAddressBookImportExport/Plugin>
#include <QVariant>

class CSVImportExportPlugin : public KAddressBookImportExport::Plugin
{
    Q_OBJECT
public:
    explicit CSVImportExportPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~CSVImportExportPlugin() override;

    PimCommon::AbstractGenericPluginInterface *createInterface(QObject *parent) override;
    [[nodiscard]] bool hasPopupMenuSupport() const override;
};
