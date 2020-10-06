/*
   SPDX-FileCopyrightText: 2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "folderconfiguresettingsgeneralwidget.h"
#include "folderconfiguresettingspagewidget.h"
#include "folderconfiguresettingstemplatewidget.h"
#include "folderconfiguresettingsviewwidget.h"
#include "folderconfiguremodifycollectionjob.h"
#include "folderconfiguresettingsexperywidget.h"
#include <MailCommon/CollectionExpiryWidget>
#include <KLocalizedString>
#include <KMessageBox>
#include <QTabWidget>
#include <QVBoxLayout>

FolderConfigureSettingsPageWidget::FolderConfigureSettingsPageWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

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

    //Expiry => add Tab
    mCollectionExpiryWidget = new FolderConfigureSettingsExperyWidget(this);
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
    if (KMessageBox::Continue ==
            KMessageBox::warningContinueCancel(this, i18n("It will override all settings for each selected folder. Do you want to continue?"),i18n("Save Folder Settings"))) {

        for (Akonadi::Collection col : cols) {
            mFolderConfigureSettingsGeneralWidget->save(col);
            mCollectionExpiryWidget->save(col);
            mFolderConfigureSettingsViewWidget->save(col);
            mCollectionTemplateWidget->save(col);
            FolderConfigureModifyCollectionJob *job = new FolderConfigureModifyCollectionJob();
            job->setCollection(col);
            job->start();
        }
    }
}
