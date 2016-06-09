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

ConfirmAddressConfigureWidget::ConfirmAddressConfigureWidget(QWidget *parent)
    : MessageComposer::PluginEditorCheckBeforeSendConfigureWidget(parent)
{
    QVBoxLayout *vboxlayout = new QVBoxLayout;
    vboxlayout->setObjectName(QStringLiteral("mainlayout"));
    setLayout(vboxlayout);
    mEnable = new QCheckBox(i18n("Enable"), this);
    mEnable->setObjectName(QStringLiteral("enable"));
    vboxlayout->addWidget(mEnable);
    connect(mEnable, &QCheckBox::clicked, this, &ConfirmAddressConfigureWidget::slotEnableChanged);

    mConfirmAddressConfigureTab = new ConfirmAddressConfigureTab(this);
    mConfirmAddressConfigureTab->setObjectName(QStringLiteral("confirmaddresstab"));
    vboxlayout->addWidget(mConfirmAddressConfigureTab);
}

ConfirmAddressConfigureWidget::~ConfirmAddressConfigureWidget()
{

}

void ConfirmAddressConfigureWidget::loadSettings()
{
#if 0
    KConfigGroup grp(KSharedConfig::openConfig(), "Confirm Address");
    mEnable->setChecked(grp.readEntry("Enabled", false));
    mDomainNameListEditor->setStringList(grp.readEntry("Domains", QStringList()));
    mWhiteListEditor->setStringList(grp.readEntry("Emails", QStringList()));
#endif
}

void ConfirmAddressConfigureWidget::saveSettings()
{
#if 0
    KConfigGroup grp(KSharedConfig::openConfig(), "Confirm Address");
    grp.writeEntry("Enabled", mEnable->isChecked());
    grp.writeEntry("Domains", mDomainNameListEditor->stringList());
    grp.writeEntry("Emails", mWhiteListEditor->stringList());
#endif
}

void ConfirmAddressConfigureWidget::resetSettings()
{
    //TODO
}

void ConfirmAddressConfigureWidget::slotEnableChanged(bool state)
{
    Q_UNUSED(state);
    Q_EMIT configureChanged();
}
