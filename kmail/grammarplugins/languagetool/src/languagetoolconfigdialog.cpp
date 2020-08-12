/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolconfigdialog.h"
#include "languagetoolconfigwidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <KSharedConfig>

LanguageToolConfigDialog::LanguageToolConfigDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure LanguageTool"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfigWidget = new LanguageToolConfigWidget(this);
    mConfigWidget->setObjectName(QStringLiteral("configwidget"));
    mainLayout->addWidget(mConfigWidget);

    QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &LanguageToolConfigDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &LanguageToolConfigDialog::reject);
    readConfig();
}

LanguageToolConfigDialog::~LanguageToolConfigDialog()
{
    writeConfig();
}

void LanguageToolConfigDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "LanguageToolConfigDialog");
    group.writeEntry("Size", size());
}

void LanguageToolConfigDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "LanguageToolConfigDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
