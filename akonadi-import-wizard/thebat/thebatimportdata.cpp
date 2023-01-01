/*
   SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "thebatimportdata.h"
#include <MailImporter/FilterInfo>
#include <MailImporter/FilterTheBat>

#include <KLocalizedString>
#include <KPluginFactory>

#include <QDir>

K_PLUGIN_CLASS_WITH_JSON(TheBatImporterFactory, "thebatimporter.json")

TheBatImportData::TheBatImportData(QObject *parent, const QList<QVariant> &)
    : LibImportWizard::AbstractImporter(parent)
{
    // TODO fix it
    mPath = QDir::homePath();
}

TheBatImportData::~TheBatImportData()
{
}

bool TheBatImportData::foundMailer() const
{
    QDir directory(mPath);
    if (directory.exists()) {
        return true;
    }
    return false;
}

QString TheBatImportData::name() const
{
    return QStringLiteral("TheBat");
}

bool TheBatImportData::importMails()
{
    MailImporter::FilterTheBat thebat;
    initializeFilter(thebat);
    thebat.filterInfo()->setStatusMessage(i18n("Import in progress"));
    QDir directory(mPath);
    if (directory.exists()) {
        thebat.importMails(mPath);
    } else {
        thebat.import();
    }
    thebat.filterInfo()->setStatusMessage(i18n("Import finished"));
    return true;
}

LibImportWizard::AbstractImporter::TypeSupportedOptions TheBatImportData::supportedOption()
{
    TypeSupportedOptions options;
    options |= LibImportWizard::AbstractImporter::Mails;
    return options;
}

#include "thebatimportdata.moc"
