/*
   Copyright (C) 2012-2020 Laurent Montel <montel@kde.org>

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

#include "evolutionv2importdata.h"
#include <MailImporter/FilterEvolution_v2>
#include <MailImporter/FilterInfo>

#include <KLocalizedString>
#include <KPluginFactory>

#include <QDir>

K_PLUGIN_CLASS_WITH_JSON(Evolutionv2ImportData, "evolutionv2importer.json")

Evolutionv2ImportData::Evolutionv2ImportData(QObject *parent, const QList<QVariant> &)
    : LibImportWizard::AbstractImporter(parent)
{
    mPath = MailImporter::FilterEvolution_v2::defaultSettingsPath();
}

Evolutionv2ImportData::~Evolutionv2ImportData()
{
}

bool Evolutionv2ImportData::foundMailer() const
{
    QDir directory(mPath);
    if (directory.exists()) {
        return true;
    }
    return false;
}

QString Evolutionv2ImportData::name() const
{
    return QStringLiteral("Evolution 2.x");
}

bool Evolutionv2ImportData::importMails()
{
    MailImporter::FilterEvolution_v2 evolution;
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

LibImportWizard::AbstractImporter::TypeSupportedOptions Evolutionv2ImportData::supportedOption()
{
    TypeSupportedOptions options;
    options |= LibImportWizard::AbstractImporter::Mails;
    return options;
}

#include "evolutionv2importdata.moc"
