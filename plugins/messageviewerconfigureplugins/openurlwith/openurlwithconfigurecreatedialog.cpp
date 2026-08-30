/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "openurlwithconfigurecreatedialog.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

OpenUrlWithConfigureCreateDialog::OpenUrlWithConfigureCreateDialog(QWidget *parent)
    : QDialog(parent)
    , mOpenUrlWithCreateWidget(new OpenUrlWithConfigureCreateWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Create"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);

    mOpenUrlWithCreateWidget->setObjectName("mOpenUrlWithCreateWidget"_L1);
    mainLayout->addWidget(mOpenUrlWithCreateWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName("buttonBox"_L1);
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &OpenUrlWithConfigureCreateDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &OpenUrlWithConfigureCreateDialog::reject);
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    okButton->setEnabled(false);
    connect(mOpenUrlWithCreateWidget, &OpenUrlWithConfigureCreateWidget::updateOkButton, this, [okButton](bool enabled) {
        okButton->setEnabled(enabled);
    });
}

OpenUrlWithConfigureCreateDialog::~OpenUrlWithConfigureCreateDialog() = default;

OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo OpenUrlWithConfigureCreateDialog::info() const
{
    return mOpenUrlWithCreateWidget->info();
}

void OpenUrlWithConfigureCreateDialog::setInfo(const OpenUrlWithConfigureCreateWidget::OpenUrlWithInfo &i)
{
    setWindowTitle(i18nc("@title:window", "Edit"));
    mOpenUrlWithCreateWidget->setInfo(i);
}

#include "moc_openurlwithconfigurecreatedialog.cpp"
