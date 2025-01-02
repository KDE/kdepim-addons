/*
   SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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

Evolutionv2ImportData::~Evolutionv2ImportData() = default;

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
