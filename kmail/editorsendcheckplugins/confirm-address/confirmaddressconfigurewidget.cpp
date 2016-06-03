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
    //TODO
}
