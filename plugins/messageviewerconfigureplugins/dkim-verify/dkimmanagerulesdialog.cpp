/*
   Copyright (C) 2019 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dkimmanagerulesdialog.h"
#include "dkimmanageruleswidget.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>

namespace {
static const char myConfigGroupName[] = "DKIMManageRulesDialog";
}

DKIMManageRulesDialog::DKIMManageRulesDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mRulesWidget = new DKIMManageRulesWidget(this);
    mRulesWidget->setObjectName(QStringLiteral("mRulesWidget"));
    mainLayout->addWidget(mRulesWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &DKIMManageRulesDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DKIMManageRulesDialog::reject);
    mRulesWidget->loadSettings();
    readConfig();
}

DKIMManageRulesDialog::~DKIMManageRulesDialog()
{

}

void DKIMManageRulesDialog::slotAccepted()
{
    mRulesWidget->saveSettings();
    accept();
}

void DKIMManageRulesDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void DKIMManageRulesDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    group.writeEntry("Size", size());
    group.sync();
}
