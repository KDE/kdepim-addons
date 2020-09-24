/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsgeneralwidget.h"
#include "folderconfiguresettingspagewidget.h"
#include "folderconfiguresettingstemplatewidget.h"
#include "folderconfiguresettingsviewwidget.h"
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

    //General
    mFolderConfigureSettingsGeneralWidget = new FolderConfigureSettingsGeneralWidget(this);
    mFolderConfigureSettingsGeneralWidget->setObjectName(QStringLiteral("mFolderConfigureSettingsGeneralWidget"));
    tab->addTab(mFolderConfigureSettingsGeneralWidget, i18n("General"));

    //View
    mFolderConfigureSettingsViewWidget = new FolderConfigureSettingsViewWidget(this);
    mFolderConfigureSettingsViewWidget->setObjectName(QStringLiteral("mFolderConfigureSettingsViewWidget"));
    tab->addTab(mFolderConfigureSettingsViewWidget, i18n("View"));

    //Expiry
    mCollectionExpiryWidget = new MailCommon::CollectionExpiryWidget(this);
    mCollectionExpiryWidget->setObjectName(QStringLiteral("mCollectionExpiryWidget"));
    tab->addTab(mCollectionExpiryWidget, i18n("Expiry"));

    //Template
    mCollectionTemplateWidget = new FolderConfigureSettingsTemplateWidget(this);
    mCollectionTemplateWidget->setObjectName(QStringLiteral("mCollectionTemplateWidget"));
    tab->addTab(mCollectionTemplateWidget, i18n("Template"));
}

FolderConfigureSettingsPageWidget::~FolderConfigureSettingsPageWidget()
{
}

void FolderConfigureSettingsPageWidget::save(const Akonadi::Collection::List &cols)
{
    for (Akonadi::Collection col : cols) {
        //TODO
        mFolderConfigureSettingsGeneralWidget->save(col);
        //TODO mCollectionExpiryWidget->save();
        mFolderConfigureSettingsViewWidget->save(col);
        mCollectionTemplateWidget->save(col);
    }
}
