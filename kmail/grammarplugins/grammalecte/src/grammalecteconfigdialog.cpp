/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteconfigdialog.h"
#include "grammalecteconfigwidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <KSharedConfig>

GrammalecteConfigDialog::GrammalecteConfigDialog(QWidget *parent, bool disableMessageBox)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure Grammalecte"));
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfigWidget = new GrammalecteConfigWidget(this, disableMessageBox);
    mConfigWidget->setObjectName(QStringLiteral("configwidget"));
    mainLayout->addWidget(mConfigWidget);

    QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &GrammalecteConfigDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &GrammalecteConfigDialog::reject);
    readConfig();
}

GrammalecteConfigDialog::~GrammalecteConfigDialog()
{
    writeConfig();
}

void GrammalecteConfigDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "GrammalecteConfigDialog");
    group.writeEntry("Size", size());
}

void GrammalecteConfigDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "GrammalecteConfigDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
