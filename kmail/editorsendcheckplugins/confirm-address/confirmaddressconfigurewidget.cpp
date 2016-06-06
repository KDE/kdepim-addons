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

#include "confirmaddressconfigurewidget.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <PimCommon/SimpleStringlistEditor>

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

    QGroupBox *groupBoxDomainName = new QGroupBox(i18n("Accepted Domain Name"), this);
    groupBoxDomainName->setObjectName(QStringLiteral("groupboxdomainname"));
    vboxlayout->addWidget(groupBoxDomainName);
    QLayout *layoutDomainName = new QVBoxLayout(groupBoxDomainName);
    layoutDomainName->setObjectName(QStringLiteral("layoutdomainname"));

    PimCommon::SimpleStringListEditor::ButtonCode buttonCode =
        static_cast<PimCommon::SimpleStringListEditor::ButtonCode>(PimCommon::SimpleStringListEditor::Add | PimCommon::SimpleStringListEditor::Remove | PimCommon::SimpleStringListEditor::Modify);
    mDomainNameListEditor =
        new PimCommon::SimpleStringListEditor(groupBoxDomainName, buttonCode,
                i18n("A&dd..."), i18n("Re&move"),
                i18n("Mod&ify..."),
                i18n("Enter new domain name:"));
    mDomainNameListEditor->setObjectName(QStringLiteral("domainnamelisteditor"));
    connect(mDomainNameListEditor, &PimCommon::SimpleStringListEditor::changed,
            this, &ConfirmAddressConfigureWidget::configureChanged);


    QGroupBox *groupBoxWhiteList = new QGroupBox(i18n("White List Address"), this);
    groupBoxWhiteList->setObjectName(QStringLiteral("groupboxwhitelist"));
    vboxlayout->addWidget(groupBoxWhiteList);
    QLayout *layoutWhiteList = new QVBoxLayout(groupBoxWhiteList);
    layoutWhiteList->setObjectName(QStringLiteral("layoutwhitelist"));

    buttonCode =
        static_cast<PimCommon::SimpleStringListEditor::ButtonCode>(PimCommon::SimpleStringListEditor::Add | PimCommon::SimpleStringListEditor::Remove | PimCommon::SimpleStringListEditor::Modify);
    mWhiteListEditor =
        new PimCommon::SimpleStringListEditor(groupBoxWhiteList, buttonCode,
                i18n("A&dd..."), i18n("Re&move"),
                i18n("Mod&ify..."),
                i18n("Enter new email name:"));
    mWhiteListEditor->setObjectName(QStringLiteral("whitelisteditor"));
    connect(mWhiteListEditor, &PimCommon::SimpleStringListEditor::changed,
            this, &ConfirmAddressConfigureWidget::configureChanged);

}

ConfirmAddressConfigureWidget::~ConfirmAddressConfigureWidget()
{

}

void ConfirmAddressConfigureWidget::loadSettings()
{
    //TODO
}

void ConfirmAddressConfigureWidget::saveSettings()
{
    //TODO
}

void ConfirmAddressConfigureWidget::resetSettings()
{
    //TODO
}

void ConfirmAddressConfigureWidget::slotEnableChanged(bool state)
{
    Q_EMIT configureChanged();
    //TODO
}
