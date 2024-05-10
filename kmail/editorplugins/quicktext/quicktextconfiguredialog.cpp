/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "quicktextconfiguredialog.h"
#include "quicktextconfigurewidget.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QCloseEvent>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
static const char myConfigGroupName[] = "QuickTextConfigureDialog";
}
QuickTextConfigureDialog::QuickTextConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mQuickTextConfigureWidget(new QuickTextConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure quick text"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mQuickTextConfigureWidget->setObjectName(QLatin1StringView("quicktextconfigurewidget"));
    mainLayout->addWidget(mQuickTextConfigureWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QLatin1StringView("buttonbox"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QuickTextConfigureDialog::slotAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QuickTextConfigureDialog::reject);

    auto importButton = new QPushButton(i18n("Import…"), this);
    buttonBox->addButton(importButton, QDialogButtonBox::ActionRole);
    connect(importButton, &QPushButton::clicked, this, &QuickTextConfigureDialog::slotImport);
    auto exportButton = new QPushButton(i18n("Export…"), this);
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
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void QuickTextConfigureDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(300, 350));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myConfigGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
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

#include "moc_quicktextconfiguredialog.cpp"
