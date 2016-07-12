/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "automaticaddcontactsconfigurewidget.h"
#include <AkonadiCore/Collection>
#include <AkonadiWidgets/CollectionComboBox>
#include <KContacts/Addressee>
#include <KLocalizedString>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QLabel>
#include <KConfigGroup>
#include <KSharedConfig>

AutomaticAddContactsWidget::AutomaticAddContactsWidget(QWidget *parent, QAbstractItemModel *model)
    : MessageComposer::PluginEditorCheckBeforeSendConfigureWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mEnabled = new QCheckBox(i18n("Automatic Add Contacts"), this);
    mEnabled->setObjectName(QStringLiteral("enabled"));
    connect(mEnabled, &QCheckBox::clicked, this, &AutomaticAddContactsWidget::configureChanged);
    mainLayout->addWidget(mEnabled);

    QHBoxLayout *hlay = new QHBoxLayout;
    hlay->setMargin(0);
    hlay->setObjectName(QStringLiteral("folderlayout"));
    mainLayout->addLayout(hlay);

    QLabel *lab = new QLabel(i18n("Select the addressbook to store contacts:"), this);
    lab->setObjectName(QStringLiteral("labelfolder"));
    hlay->addWidget(lab);


    mCollectionCombobox = new Akonadi::CollectionComboBox(model);
    mCollectionCombobox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
    mCollectionCombobox->setMinimumWidth(250);
    mCollectionCombobox->setMimeTypeFilter(QStringList() << KContacts::Addressee::mimeType());
    mCollectionCombobox->setObjectName(QStringLiteral("akonadicombobox"));
    hlay->addWidget(mCollectionCombobox);
    connect(mCollectionCombobox, static_cast<void (Akonadi::CollectionComboBox::*)(int)>(&Akonadi::CollectionComboBox::currentIndexChanged),
            this, &AutomaticAddContactsWidget::configureChanged);
    connect(mCollectionCombobox, static_cast<void (Akonadi::CollectionComboBox::*)(int)>(&Akonadi::CollectionComboBox::activated),
            this, &AutomaticAddContactsWidget::configureChanged);


    mainLayout->addStretch(1);
}

AutomaticAddContactsWidget::~AutomaticAddContactsWidget()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Automatic Add Contacts");
    mEnabled->setChecked(grp.readEntry("Enabled", false));
}

void AutomaticAddContactsWidget::loadSettings()
{
}

void AutomaticAddContactsWidget::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Automatic Add Contacts");
    grp.writeEntry("Enabled", mEnabled->isChecked());
    grp.writeEntry("Collection", mCollectionCombobox->currentCollection().id());
}

void AutomaticAddContactsWidget::resetSettings()
{
    mEnabled->setChecked(false);
}
