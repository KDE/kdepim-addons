/*
   Copyright (C) 2017-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
        const QString fullPath = lstDir.at(i) + QDir::separator() + configName;
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
