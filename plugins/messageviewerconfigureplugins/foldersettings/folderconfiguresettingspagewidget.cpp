/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsgeneralwidget.h"
#include "folderconfiguresettingspagewidget.h"
#include <MailCommon/CollectionExpiryWidget>
#include <KLocalizedString>
#include <QTabWidget>
#include <QVBoxLayout>

FolderConfigureSettingsPageWidget::FolderConfigureSettingsPageWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QTabWidget *tab = new QTabWidget(this);
    tab->setObjectName(QStringLiteral("tab"));
    mainLayout->addWidget(tab);

    mFolderConfigureSettingsGeneralWidget = new FolderConfigureSettingsGeneralWidget(this);
    mFolderConfigureSettingsGeneralWidget->setObjectName(QStringLiteral("mFolderConfigureSettingsGeneralWidget"));
    tab->addTab(mFolderConfigureSettingsGeneralWidget, i18n("General"));

    mCollectionExpiryWidget = new MailCommon::CollectionExpiryWidget(this);
    mCollectionExpiryWidget->setObjectName(QStringLiteral("mCollectionExpiryWidget"));
    tab->addTab(mCollectionExpiryWidget, i18n("Expiry"));
    //configure expire folder
    //Preference mail
    //General
}

FolderConfigureSettingsPageWidget::~FolderConfigureSettingsPageWidget()
{

}

void FolderConfigureSettingsPageWidget::save()
{

}
