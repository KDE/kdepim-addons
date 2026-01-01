/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "evolutionv1importdata.h"
#include <MailImporter/FilterEvolution>
#include <MailImporter/FilterInfo>

#include <KLocalizedString>
#include <KPluginFactory>

#include <QDir>

K_PLUGIN_CLASS_WITH_JSON(Evolutionv1ImportData, "evolutionv1importer.json")

Evolutionv1ImportData::Evolutionv1ImportData(QObject *parent, const QList<QVariant> &)
    : LibImportWizard::AbstractImporter(parent)
{
    mPath = MailImporter::FilterEvolution::defaultSettingsPath();
}

Evolutionv1ImportData::~Evolutionv1ImportData() = default;

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
