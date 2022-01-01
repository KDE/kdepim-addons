/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolconfigdialog.h"
#include "languagetoolconfigwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

namespace
{
static const char myConfigGroupName[] = "LanguageToolConfigDialog";
}
LanguageToolConfigDialog::LanguageToolConfigDialog(QWidget *parent)
    : QDialog(parent)
    , mConfigWidget(new LanguageToolConfigWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure LanguageTool"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mConfigWidget->setObjectName(QStringLiteral("configwidget"));
    mainLayout->addWidget(mConfigWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel | QDialogButtonBox::Reset, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &LanguageToolConfigDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &LanguageToolConfigDialog::reject);
    connect(box->button(QDialogButtonBox::Reset), &QPushButton::clicked, mConfigWidget, &LanguageToolConfigWidget::resetValue);
    readConfig();
}

LanguageToolConfigDialog::~LanguageToolConfigDialog()
{
    writeConfig();
}

void LanguageToolConfigDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    group.writeEntry("Size", size());
}

void LanguageToolConfigDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
