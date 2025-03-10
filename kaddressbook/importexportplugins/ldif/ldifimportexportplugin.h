/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KAddressBookImportExport/Plugin>
#include <QVariant>

class LDifImportExportPlugin : public KAddressBookImportExport::Plugin
{
    Q_OBJECT
public:
    explicit LDifImportExportPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~LDifImportExportPlugin() override;

    [[nodiscard]] PimCommon::AbstractGenericPluginInterface *createInterface(QObject *parent) override;
    [[nodiscard]] bool hasPopupMenuSupport() const override;
};
