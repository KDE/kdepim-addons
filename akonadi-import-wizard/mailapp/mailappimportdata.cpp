/*
   SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mailappimportdata.h"
#include <MailImporter/FilterInfo>
#include <MailImporter/FilterMailApp>

#include <KLocalizedString>
#include <KPluginFactory>
#include <QDir>

K_PLUGIN_CLASS_WITH_JSON(MailAppImportData, "mailappimporter.json")

MailAppImportData::MailAppImportData(QObject *parent, const QList<QVariant> &)
    : LibImportWizard::AbstractImporter(parent)
{
    mPath = QDir::homePath();
}

MailAppImportData::~MailAppImportData()
{
}

bool MailAppImportData::foundMailer() const
{
#ifdef Q_OS_MAC
    // TODO find a method to search it. Perhaps look at binary.
    QDir directory(mPath);
    if (directory.exists()) {
        return true;
    }
#endif
    return false;
}

QString MailAppImportData::name() const
{
    return QStringLiteral("Mail App");
}

bool MailAppImportData::importMails()
{
    MailImporter::FilterMailApp mailapp;
    initializeFilter(mailapp);
    mailapp.filterInfo()->setStatusMessage(i18n("Import in progress"));
    QDir directory(mPath);
    if (directory.exists()) {
        mailapp.importMails(mPath);
    } else {
        mailapp.import();
    }
    mailapp.filterInfo()->setStatusMessage(i18n("Import finished"));
    return true;
}

LibImportWizard::AbstractImporter::TypeSupportedOptions MailAppImportData::supportedOption()
{
    TypeSupportedOptions options;
    options |= LibImportWizard::AbstractImporter::Mails;
    return options;
}

#include "mailappimportdata.moc"
