/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockblockableitemsdialog.h"
#include "adblockblockableitemswidget.h"

#include <KLocalizedString>
#include <KTreeWidgetSearchLine>

#include <KConfigGroup>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
namespace
{
static const char myConfigAdBlockBlockableItemsDialog[] = "AdBlockBlockableItemsDialog";
}
using namespace AdBlock;
AdBlockBlockableItemsDialog::AdBlockBlockableItemsDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Blockable Items"));

    auto mainLayout = new QVBoxLayout(this);

    mBlockableItems = new AdBlockBlockableItemsWidget(this);
    mBlockableItems->setObjectName(QStringLiteral("blockableitemswidget"));

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
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
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigAdBlockBlockableItemsDialog);
    group.writeEntry("Size", size());
}

void AdBlockBlockableItemsDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigAdBlockBlockableItemsDialog);
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
