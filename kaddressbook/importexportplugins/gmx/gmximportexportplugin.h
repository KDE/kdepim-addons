/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GMXIMPORTEXPORTPLUGIN_H
#define GMXIMPORTEXPORTPLUGIN_H

#include <KAddressBookImportExport/Plugin>
#include <QVariant>

class GMXImportExportPlugin : public KAddressBookImportExport::Plugin
{
    Q_OBJECT
public:
    explicit GMXImportExportPlugin(QObject *parent = nullptr, const QList<QVariant> & = {});
    ~GMXImportExportPlugin() override;

    PimCommon::AbstractGenericPluginInterface *createInterface(QObject *parent) override;
    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
};

#endif // GMXIMPORTEXPORTPLUGIN_H
