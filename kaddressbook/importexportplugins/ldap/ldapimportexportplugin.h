/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LDAPIMPORTEXPORTPLUGIN_H
#define LDAPIMPORTEXPORTPLUGIN_H
#include <KAddressBookImportExport/KAddressBookImportExportPlugin>
#include <QVariant>
class LDapImportExportPlugin : public KAddressBookImportExport::KAddressBookImportExportPlugin
{
    Q_OBJECT
public:
    explicit LDapImportExportPlugin(QObject *parent = nullptr, const QList<QVariant> & =
    {
    });
    ~LDapImportExportPlugin() override;

    PimCommon::AbstractGenericPluginInterface *createInterface(QObject *parent) override;
    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
};

#endif // LDAPIMPORTEXPORTPLUGIN_H
