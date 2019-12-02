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

#include "evolutionv1importdata.h"
#include "mailimporter/filterevolution.h"
#include "mailimporter/filterinfo.h"

#include <KLocalizedString>
#include <KPluginFactory>

#include <QDir>

K_PLUGIN_CLASS_WITH_JSON(Evolutionv1ImportData, "evolutionv1importer.json")

Evolutionv1ImportData::Evolutionv1ImportData(QObject *parent, const QList<QVariant> &)
    : LibImportWizard::AbstractImporter(parent)
{
    mPath = MailImporter::FilterEvolution::defaultSettingsPath();
}

Evolutionv1ImportData::~Evolutionv1ImportData()
{
}

bool Evolutionv1ImportData::foundMailer() const
{
    QDir directory(mPath);
    if (directory.exists()) {
        return true;
    }
    return false;
}

QString Evolutionv1ImportData::name() const
{
    return QStringLiteral("Evolution 1.x");
}

bool Evolutionv1ImportData::importMails()
{
    MailImporter::FilterEvolution evolution;
    initializeFilter(evolution);
    evolution.filterInfo()->setStatusMessage(i18n("Import in progress"));
    const QString mailsPath = mPath;
    QDir directory(mailsPath);
    if (directory.exists()) {
        evolution.importMails(mailsPath);
    } else {
        evolution.import();
    }
    evolution.filterInfo()->setStatusMessage(i18n("Import finished"));
    return true;
}

LibImportWizard::AbstractImporter::TypeSupportedOptions Evolutionv1ImportData::supportedOption()
{
    TypeSupportedOptions options;
    options |= LibImportWizard::AbstractImporter::Mails;
    return options;
}

#include "evolutionv1importdata.moc"
