/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CSVIMPORTEXPORTPLUGIN_H
#define CSVIMPORTEXPORTPLUGIN_H

#include <KAddressBookImportExport/Plugin>
#include <QVariant>

class CSVImportExportPlugin : public KAddressBookImportExport::Plugin
{
    Q_OBJECT
public:
    explicit CSVImportExportPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~CSVImportExportPlugin() override;

    PimCommon::AbstractGenericPluginInterface *createInterface(QObject *parent) override;
    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
};

#endif // CSVIMPORTEXPORTPLUGIN_H
