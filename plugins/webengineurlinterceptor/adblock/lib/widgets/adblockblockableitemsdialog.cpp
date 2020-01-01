/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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

#include "adblockblockableitemsdialog.h"
#include "adblockblockableitemswidget.h"

#include <KLocalizedString>
#include <KTreeWidgetSearchLine>

#include <QVBoxLayout>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <QPushButton>
using namespace AdBlock;
AdBlockBlockableItemsDialog::AdBlockBlockableItemsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Blockable Items"));

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    mBlockableItems = new AdBlockBlockableItemsWidget(this);
    mBlockableItems->setObjectName(QStringLiteral("blockableitemswidget"));

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AdBlockBlockableItemsDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AdBlockBlockableItemsDialog::reject);

    mainLayout->addWidget(mBlockableItems);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

AdBlockBlockableItemsDialog::~AdBlockBlockableItemsDialog()
{
    writeConfig();
}

void AdBlockBlockableItemsDialog::accept()
{
    saveFilters();
    QDialog::accept();
}

void AdBlockBlockableItemsDialog::saveFilters()
{
    mBlockableItems->saveFilters();
}

void AdBlockBlockableItemsDialog::setAdblockResult(const QVector<AdBlock::AdBlockResult> &result)
{
    mBlockableItems->setAdblockResult(result);
}

void AdBlockBlockableItemsDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "AdBlockBlockableItemsDialog");
    group.writeEntry("Size", size());
}

void AdBlockBlockableItemsDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "AdBlockBlockableItemsDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
