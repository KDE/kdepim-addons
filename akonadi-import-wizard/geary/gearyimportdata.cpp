/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gearyimportdata.h"
#include "gearyaddressbook.h"
#include "gearysettings.h"
#include <MailImporter/FilterInfo>
#include <MailImporter/OtherMailerUtil>

#include "gearyplugin_debug.h"
#include <KPluginFactory>
#include <QDir>

K_PLUGIN_CLASS_WITH_JSON(GearyImportData, "gearyimporter.json")

GearyImportData::GearyImportData(QObject *parent, const QList<QVariant> &)
    : LibImportWizard::AbstractImporter(parent)
{
    mPath = MailImporter::OtherMailerUtil::gearyDefaultPath();
}

GearyImportData::~GearyImportData() = default;

bool GearyImportData::foundMailer() const
{
    QDir directory(mPath);
    if (directory.exists()) {
        return true;
    }
    return false;
}

QString GearyImportData::name() const
{
    return QStringLiteral("Geary");
}

bool GearyImportData::importMails()
{
    return false;
}

bool GearyImportData::importSettings()
{
    QDir directory(mPath);
    const QStringList lstDir = directory.entryList(QDir::AllDirs);
    qCDebug(GEARYPLUGIN_LOG) << "Number of directory " << lstDir.count();
    const QString configName = QStringLiteral("geary.ini");
    for (int i = 0; i < lstDir.count(); ++i) {
        const QString fullPath = lstDir.at(i) + QLatin1Char('/') + configName;
        if (QFileInfo::exists(fullPath)) {
            GearySettings setting(fullPath);
            setting.setAbstractDisplayInfo(mAbstractDisplayInfo);
            setting.importSettings();
        }
    }
    return true;
}

bool GearyImportData::importAddressBook()
{
    return false;
}

LibImportWizard::AbstractImporter::TypeSupportedOptions GearyImportData::supportedOption()
{
    TypeSupportedOptions options;
    // options |=LibImportWizard::AbstractImporter::Mails;
    options |= LibImportWizard::AbstractImporter::Settings;
    // options |= LibImportWizard::AbstractImporter::AddressBooks;
    return options;
}

#include "gearyimportdata.moc"
