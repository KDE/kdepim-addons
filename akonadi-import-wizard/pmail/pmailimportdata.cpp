/*
   Copyright (C) 2012-2017 Montel Laurent <montel@kde.org>

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

#include "pmailimportdata.h"
#include "pmailsettings.h"
#include "mailimporter/filterpmail.h"
#include "mailimporter/filterinfo.h"

#include <KLocalizedString>
#include <kpluginfactory.h>
#include <QDir>

K_PLUGIN_FACTORY_WITH_JSON(PMailImporterFactory, "pmailimporter.json", registerPlugin<PMailImportData>();
                           )
PMailImportData::PMailImportData(QObject *parent, const QList<QVariant> &)
    : LibImportWizard::AbstractImporter(parent)
{
    mPath = QDir::homePath();
}

PMailImportData::~PMailImportData()
{
}

bool PMailImportData::foundMailer() const
{
#ifdef Q_OS_WIN
    //TODO find a method to search it. Perhaps look at binary.
    QDir directory(mPath);
    if (directory.exists()) {
        return true;
    }
#endif
    return false;
}

QString PMailImportData::name() const
{
    return QStringLiteral("Pegasus Mail");
}

bool PMailImportData::importMails()
{
    MailImporter::FilterPMail pmail;
    initializeFilter(pmail);
    pmail.filterInfo()->setStatusMessage(i18n("Import in progress"));
    QDir directory(mPath);
    if (directory.exists()) {
        pmail.importMails(mPath);
    } else {
        pmail.import();
    }
    pmail.filterInfo()->setStatusMessage(i18n("Import finished"));
    return true;
}

bool PMailImportData::importSettings()
{
    //TODO verify path
    const QString settingFile(mPath + QLatin1String("pmail.ini"));
    PMailSettings settings(settingFile);
    settings.setAbstractDisplayInfo(mAbstractDisplayInfo);
    settings.importSettings();
    return true;
}

LibImportWizard::AbstractImporter::TypeSupportedOptions PMailImportData::supportedOption()
{
    TypeSupportedOptions options;
    options |= LibImportWizard::AbstractImporter::Mails;
    //options |=LibImportWizard::AbstractImporter::Settings;
    return options;
}

#include "pmailimportdata.moc"
