/*
   Copyright (C) 2018-2019 Laurent Montel <montel@kde.org>

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

#include "dkimconfiguredialog.h"
#include "dkimconfigurewidget.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>

using namespace MessageViewer;
DKIMConfigureDialog::DKIMConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfigureWidget = new DKIMConfigureWidget(this);
    mConfigureWidget->setObjectName(QStringLiteral("mConfigureWidget"));
    mainLayout->addWidget(mConfigureWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::RestoreDefaults, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &DKIMConfigureDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &DKIMConfigureDialog::reject);
    connect(buttonBox->button(QDialogButtonBox::RestoreDefaults), &QPushButton::clicked, this, &DKIMConfigureDialog::slotReset);
    mConfigureWidget->loadSettings();
}

DKIMConfigureDialog::~DKIMConfigureDialog()
{
}

void DKIMConfigureDialog::slotAccepted()
{
    mConfigureWidget->saveSettings();
    accept();
}

void DKIMConfigureDialog::slotReset()
{
    mConfigureWidget->resetSettings();
}

void DKIMConfigureDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "DKIMConfigureDialog");
    const QSize size = group.readEntry("Size", QSize(600, 400));
    if (size.isValid()) {
        resize(size);
    }
}

void DKIMConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "DKIMConfigureDialog");
    group.writeEntry("Size", size());
    group.sync();
}
