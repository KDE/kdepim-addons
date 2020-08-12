/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "nylasmaildata.h"
#include "nylasmailsettings.h"
#include <MailImporter/FilterInfo>
#include <MailImporter/OtherMailerUtil>

#include "nylasmailplugin_debug.h"
#include <KPluginFactory>
#include <QDir>

K_PLUGIN_CLASS_WITH_JSON(NylasMailImportData, "nylasmailimporter.json")

NylasMailImportData::NylasMailImportData(QObject *parent, const QList<QVariant> &)
    : LibImportWizard::AbstractImporter(parent)
{
    mPath = MailImporter::OtherMailerUtil::nylasMailDefaultPath();
}

NylasMailImportData::~NylasMailImportData()
{
}

bool NylasMailImportData::foundMailer() const
{
    QDir directory(mPath);
    if (directory.exists()) {
        return true;
    }
    return false;
}

QString NylasMailImportData::name() const
{
    return QStringLiteral("NylasMail");
}

bool NylasMailImportData::importMails()
{
    return false;
}

bool NylasMailImportData::importSettings()
{
    QDir directory(mPath);
    const QStringList lstDir = directory.entryList(QDir::AllDirs);
    qCDebug(NYLASMAILPLUGIN_LOG) << "Number of directory " << lstDir.count();
    /*
    const QString configName = QStringLiteral("NylasMail.ini");
    for (int i = 0; i < lstDir.count(); ++i) {
        const QString fullPath = lstDir.at(i) + QLatin1Char('/') + configName;
        if (QFileInfo::exists(fullPath)) {
            NylasMailSettings setting(fullPath);
            setting.setAbstractDisplayInfo(mAbstractDisplayInfo);
            setting.importSettings();
        }
    }
    */
    return true;
}

bool NylasMailImportData::importAddressBook()
{
    return false;
}

LibImportWizard::AbstractImporter::TypeSupportedOptions NylasMailImportData::supportedOption()
{
    TypeSupportedOptions options;
    //options |=LibImportWizard::AbstractImporter::Mails;
    //Disable it for the moment
    //options |= LibImportWizard::AbstractImporter::Settings;
    //options |= LibImportWizard::AbstractImporter::AddressBooks;
    return options;
}

#include "nylasmaildata.moc"
