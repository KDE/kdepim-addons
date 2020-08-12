/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VCARDIMPORTEXPORTPLUGIN_H
#define VCARDIMPORTEXPORTPLUGIN_H
#include <KAddressBookImportExport/KAddressBookImportExportPlugin>
#include <QVariant>
class VCardImportExportPlugin : public KAddressBookImportExport::KAddressBookImportExportPlugin
{
    Q_OBJECT
public:
    explicit VCardImportExportPlugin(QObject *parent = nullptr, const QList<QVariant> & =
    {
    });
    ~VCardImportExportPlugin() override;

    PimCommon::AbstractGenericPluginInterface *createInterface(QObject *parent) override;
    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
};

#endif // VCARDIMPORTEXPORTPLUGIN_H
