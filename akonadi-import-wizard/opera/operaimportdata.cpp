/*
   SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "operaimportdata.h"
#include "operaaddressbook.h"
#include "operasettings.h"
#include <MailImporter/FilterInfo>
#include <MailImporter/FilterOpera>

#include <KLocalizedString>
#include <KPluginFactory>
#include <QDir>

K_PLUGIN_CLASS_WITH_JSON(OperaImportData, "operaimporter.json")

OperaImportData::OperaImportData(QObject *parent, const QList<QVariant> &)
    : LibImportWizard::AbstractImporter(parent)
{
    mPath = MailImporter::FilterOpera::defaultSettingsPath();
}

OperaImportData::~OperaImportData() = default;

bool OperaImportData::foundMailer() const
{
    QDir directory(mPath);
    if (directory.exists()) {
        return true;
    }
    return false;
}

QString OperaImportData::name() const
{
    return QStringLiteral("Opera");
}

bool OperaImportData::importMails()
{
    MailImporter::FilterOpera opera;
    initializeFilter(opera);
    opera.filterInfo()->setStatusMessage(i18n("Import in progress"));
    const QString mailPath(mPath + QStringLiteral("mail/store/"));
    QDir directory(mailPath);
    if (directory.exists()) {
        opera.importMails(mailPath);
    } else {
        opera.import();
    }
    opera.filterInfo()->setStatusMessage(i18n("Import finished"));
    return true;
}

bool OperaImportData::importAddressBook()
{
    const QString addressbookFile(mPath + QStringLiteral("bookmarks.adr"));
    OperaAddressBook addressbook(addressbookFile);
    addressbook.setAbstractDisplayInfo(mAbstractDisplayInfo);
    addressbook.importAddressBook();
    return true;
}

bool OperaImportData::importSettings()
{
    const QString settingFile(mPath + QStringLiteral("mail/accounts.ini"));
    OperaSettings settings(settingFile);
    settings.setAbstractDisplayInfo(mAbstractDisplayInfo);
    settings.importSettings();
    return true;
}

LibImportWizard::AbstractImporter::TypeSupportedOptions OperaImportData::supportedOption()
{
    TypeSupportedOptions options;
    options |= LibImportWizard::AbstractImporter::Mails;
    options |= LibImportWizard::AbstractImporter::AddressBooks;
    options |= LibImportWizard::AbstractImporter::Settings;
    return options;
}

#include "operaimportdata.moc"
