/*
   Copyright (C) 2012-2019 Montel Laurent <montel@kde.org>

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

#include "oeimportdata.h"
#include "mailimporter/filteroe.h"
#include "mailimporter/filterinfo.h"

#include <KLocalizedString>
#include <kpluginfactory.h>

#include <QDir>

K_PLUGIN_FACTORY_WITH_JSON(OEImporterFactory, "oeimporter.json", registerPlugin<OeImportData>();
                           )

OeImportData::OeImportData(QObject *parent, const QList<QVariant> &)
    : LibImportWizard::AbstractImporter(parent)
{
    mPath = QDir::homePath();
}

OeImportData::~OeImportData()
{
}

bool OeImportData::foundMailer() const
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

QString OeImportData::name() const
{
    return QStringLiteral("Outlook Express");
}

bool OeImportData::importMails()
{
    MailImporter::FilterOE opera;
    initializeFilter(opera);
    opera.filterInfo()->setStatusMessage(i18n("Import in progress"));
    QDir directory(mPath);
    if (directory.exists()) {
        opera.importMails(mPath);
    } else {
        opera.import();
    }
    opera.filterInfo()->setStatusMessage(i18n("Import finished"));
    return true;
}

LibImportWizard::AbstractImporter::TypeSupportedOptions OeImportData::supportedOption()
{
    TypeSupportedOptions options;
    options |= LibImportWizard::AbstractImporter::Mails;
    return options;
}

#include "oeimportdata.moc"
