/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef WINDOWSCONTACTIMPORTEXPORTPLUGIN_H
#define WINDOWSCONTACTIMPORTEXPORTPLUGIN_H
#include <KAddressBookImportExport/KAddressBookImportExportPlugin>
#include <QVariant>
class WindowsContactImportExportPlugin : public KAddressBookImportExport::KAddressBookImportExportPlugin
{
    Q_OBJECT
public:
    explicit WindowsContactImportExportPlugin(QObject *parent = nullptr, const QList<QVariant> & = {
    });
    ~WindowsContactImportExportPlugin() override;

    PimCommon::AbstractGenericPluginInterface *createInterface(QObject *parent) override;
    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
};

#endif // WINDOWSCONTACTIMPORTEXPORTPLUGIN_H
