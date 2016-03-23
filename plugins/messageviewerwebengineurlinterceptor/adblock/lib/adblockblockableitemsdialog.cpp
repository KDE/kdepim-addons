/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
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

AdBlockBlockableItemsDialog::AdBlockBlockableItemsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Blockable Items"));
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    QVBoxLayout *mainLayout = new QVBoxLayout;
    setLayout(mainLayout);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDefault(true);
    okButton->setShortcut(Qt::CTRL | Qt::Key_Return);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &AdBlockBlockableItemsDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &AdBlockBlockableItemsDialog::reject);

    mBlockableItems = new AdBlockBlockableItemsWidget;
    mBlockableItems->setObjectName(QStringLiteral("blockableitemswidget"));

    mainLayout->addWidget(mBlockableItems);
    mainLayout->addWidget(buttonBox);
    readConfig();
}

AdBlockBlockableItemsDialog::~AdBlockBlockableItemsDialog()
{
    writeConfig();
}


void AdBlockBlockableItemsDialog::setWebEngineView(QWebEngineView *view)
{
    mBlockableItems->setWebEngineView(view);
}

void AdBlockBlockableItemsDialog::saveFilters()
{
    //FIXME mBlockableItems->saveFilters();
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

