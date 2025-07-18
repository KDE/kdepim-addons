/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactstabwidget.h"
using namespace Qt::Literals::StringLiterals;

#include <Akonadi/Collection>
#include <Akonadi/CollectionComboBox>
#include <KConfigGroup>
#include <KContacts/Addressee>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>

namespace
{
QString configGroupName()
{
    return u"Automatic Add Contacts %1"_s;
}
}
AutomaticAddContactsTabWidget::AutomaticAddContactsTabWidget(QWidget *parent, QAbstractItemModel *model)
    : QWidget(parent)
    , mEnabled(new QCheckBox(i18nc("@option:check", "Automatic Add Contacts"), this))
    , mCollectionCombobox(new Akonadi::CollectionComboBox(model, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mEnabled->setObjectName(QLatin1StringView("enabled"));
    connect(mEnabled, &QCheckBox::clicked, this, &AutomaticAddContactsTabWidget::configureChanged);
    mainLayout->addWidget(mEnabled);

    auto hlay = new QHBoxLayout;
    hlay->setContentsMargins({});
    hlay->setObjectName(QLatin1StringView("folderlayout"));
    mainLayout->addLayout(hlay);

    auto lab = new QLabel(i18nc("@label:textbox", "Select the addressbook in which to store contacts:"), this);
    lab->setObjectName(QLatin1StringView("labelfolder"));
    hlay->addWidget(lab);

    mCollectionCombobox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
    mCollectionCombobox->setMinimumWidth(250);
    mCollectionCombobox->setMimeTypeFilter(QStringList() << KContacts::Addressee::mimeType());
    mCollectionCombobox->setObjectName(QLatin1StringView("akonadicombobox"));
    hlay->addWidget(mCollectionCombobox);
    hlay->addStretch(1);
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::currentIndexChanged, this, &AutomaticAddContactsTabWidget::configureChanged);
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::activated, this, &AutomaticAddContactsTabWidget::configureChanged);

    mainLayout->addStretch(1);
}

AutomaticAddContactsTabWidget::~AutomaticAddContactsTabWidget() = default;

void AutomaticAddContactsTabWidget::resetSettings()
{
    mEnabled->setChecked(false);
}

void AutomaticAddContactsTabWidget::loadSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup grp = config->group(configGroupName().arg(mIdentity));
    mEnabled->setChecked(grp.readEntry("Enabled", false));
    mCollectionCombobox->setDefaultCollection(Akonadi::Collection(grp.readEntry("Collection", -1)));
}

void AutomaticAddContactsTabWidget::setIdentity(uint identity)
{
    mIdentity = identity;
}

void AutomaticAddContactsTabWidget::saveSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    KConfigGroup grp = config->group(configGroupName().arg(mIdentity));
    grp.writeEntry("Enabled", mEnabled->isChecked());
    grp.writeEntry("Collection", mCollectionCombobox->currentCollection().id());
}

#include "moc_automaticaddcontactstabwidget.cpp"
