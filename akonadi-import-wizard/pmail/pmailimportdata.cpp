/*
   SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "pmailimportdata.h"
#include "pmailsettings.h"
#include <MailImporter/FilterInfo>
#include <MailImporter/FilterPMail>

#include <KLocalizedString>
#include <KPluginFactory>
#include <QDir>

K_PLUGIN_CLASS_WITH_JSON(PMailImportData, "pmailimporter.json")
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
    // TODO find a method to search it. Perhaps look at binary.
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
    // TODO verify path
    const QString settingFile(mPath + QLatin1StringView("pmail.ini"));
    PMailSettings settings(settingFile);
    settings.setAbstractDisplayInfo(mAbstractDisplayInfo);
    settings.importSettings();
    return true;
}

LibImportWizard::AbstractImporter::TypeSupportedOptions PMailImportData::supportedOption()
{
    TypeSupportedOptions options;
    options |= LibImportWizard::AbstractImporter::Mails;
    // options |=LibImportWizard::AbstractImporter::Settings;
    return options;
}

#include "pmailimportdata.moc"
