/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "quicktextconfiguredialog.h"
#include "quicktextconfigurewidget.h"

#include <KConfigGroup>
#include <KSharedConfig>
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QCloseEvent>
#include <QPushButton>

namespace {
static const char myConfigGroupName[] = "QuickTextConfigureDialog";
}
QuickTextConfigureDialog::QuickTextConfigureDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure quick text"));
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mQuickTextConfigureWidget = new QuickTextConfigureWidget(this);
    mQuickTextConfigureWidget->setObjectName(QStringLiteral("quicktextconfigurewidget"));
    mainLayout->addWidget(mQuickTextConfigureWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QuickTextConfigureDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QuickTextConfigureDialog::reject);

    QPushButton *importButton = new QPushButton(i18n("Import..."), this);
    buttonBox->addButton(importButton, QDialogButtonBox::ActionRole);
    connect(importButton, &QPushButton::clicked, this, &QuickTextConfigureDialog::slotImport);
    QPushButton *exportButton = new QPushButton(i18n("Export..."), this);
    buttonBox->addButton(exportButton, QDialogButtonBox::ActionRole);
    connect(exportButton, &QPushButton::clicked, this, &QuickTextConfigureDialog::slotExport);

    mainLayout->addWidget(buttonBox);
    writeConfig();
}

QuickTextConfigureDialog::~QuickTextConfigureDialog()
{
    readConfig();
}

void QuickTextConfigureDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    group.writeEntry("Size", size());
}

void QuickTextConfigureDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), myConfigGroupName);
    const QSize sizeDialog = group.readEntry("Size", QSize(300, 350));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void QuickTextConfigureDialog::slotImport()
{
    mQuickTextConfigureWidget->importQuickText();
}

void QuickTextConfigureDialog::slotExport()
{

    mQuickTextConfigureWidget->exportQuickText();
}

void QuickTextConfigureDialog::closeEvent(QCloseEvent *e)
{
    mQuickTextConfigureWidget->save();
    e->accept();
}

void QuickTextConfigureDialog::slotAccepted()
{
    mQuickTextConfigureWidget->save();
    QDialog::accept();
}
