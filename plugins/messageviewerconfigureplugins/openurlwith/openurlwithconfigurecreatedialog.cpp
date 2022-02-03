/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "openurlwithconfigurecreatedialog.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

OpenUrlWithConfigureCreateDialog::OpenUrlWithConfigureCreateDialog(QWidget *parent)
    : QDialog(parent)
    , mOpenUrlWithCreateWidget(new OpenUrlWithConfigureCreateWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Open Url With Plugin"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mOpenUrlWithCreateWidget->setObjectName(QStringLiteral("mOpenUrlWithCreateWidget"));
    mainLayout->addWidget(mOpenUrlWithCreateWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &OpenUrlWithConfigureCreateDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &OpenUrlWithConfigureCreateDialog::reject);
}

OpenUrlWithConfigureCreateDialog::~OpenUrlWithConfigureCreateDialog()
{
}

OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo OpenUrlWithConfigureCreateDialog::info() const
{
    return mOpenUrlWithCreateWidget->info();
}

void OpenUrlWithConfigureCreateDialog::setInfo(const OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo &i)
{
    mOpenUrlWithCreateWidget->setInfo(i);
}