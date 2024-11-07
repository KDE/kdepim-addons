/*
   SPDX-FileCopyrightText: 2012-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "oeimportdata.h"
#include <MailImporter/FilterInfo>
#include <MailImporter/FilterOE>

#include <KLocalizedString>
#include <KPluginFactory>

#include <QDir>

K_PLUGIN_CLASS_WITH_JSON(OeImportData, "oeimporter.json")

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
    // TODO find a method to search it. Perhaps look at binary.
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
