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

#include "confirmaddressconfiguretab.h"
#include "confirmaddressconfigurewidget.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QVBoxLayout>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QRegularExpression>

ConfirmAddressConfigureWidget::ConfirmAddressConfigureWidget(KIdentityManagement::IdentityManager *identityManager, QWidget *parent)
    : MessageComposer::PluginEditorCheckBeforeSendConfigureWidget(identityManager, parent)
{
    QVBoxLayout *vboxlayout = new QVBoxLayout;
    vboxlayout->setObjectName(QStringLiteral("mainlayout"));
    setLayout(vboxlayout);
    mEnable = new QCheckBox(i18n("Enable"), this);
    mEnable->setObjectName(QStringLiteral("enable"));
    vboxlayout->addWidget(mEnable);
    connect(mEnable, &QCheckBox::clicked, this, &ConfirmAddressConfigureWidget::slotEnableChanged);

    mConfirmAddressConfigureTab = new ConfirmAddressConfigureTab(identityManagement(), this);
    mConfirmAddressConfigureTab->setObjectName(QStringLiteral("confirmaddresstab"));
    connect(mConfirmAddressConfigureTab, &ConfirmAddressConfigureTab::configureChanged, this, &ConfirmAddressConfigureWidget::configureChanged);
    vboxlayout->addWidget(mConfirmAddressConfigureTab);
}

ConfirmAddressConfigureWidget::~ConfirmAddressConfigureWidget()
{

}

void ConfirmAddressConfigureWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Confirm Address");
    mEnable->setChecked(grp.readEntry("Enabled", false));
    mConfirmAddressConfigureTab->loadSettings(grp);
}

void ConfirmAddressConfigureWidget::saveSettings()
{
    KSharedConfig::Ptr config = KSharedConfig::openConfig();
    // first, delete all filter groups:
    const QStringList filterGroups = config->groupList().filter(QRegularExpression(QStringLiteral("Confirm Address \\d+")));
    Q_FOREACH (const QString &group, filterGroups) {
        config->deleteGroup(group);
    }
    KConfigGroup grp(config, "Confirm Address");
    grp.writeEntry("Enabled", mEnable->isChecked());
    mConfirmAddressConfigureTab->saveSettings(grp);
}

void ConfirmAddressConfigureWidget::resetSettings()
{
    mConfirmAddressConfigureTab->resetSettings();
}

void ConfirmAddressConfigureWidget::slotEnableChanged(bool state)
{
    Q_UNUSED(state);
    Q_EMIT configureChanged();
}
