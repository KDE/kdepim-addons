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
{
    setWindowTitle(i18nc("@title:window", "Configure Open Url With Plugin"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    //    mOpenUrlWithWidget->setObjectName(QStringLiteral("mOpenUrlWithWidget"));
    //    mainLayout->addWidget(mOpenUrlWithWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);

    //    connect(buttonBox, &QDialogButtonBox::accepted, this, &OpenUrlWithConfigureDialog::slotAccepted);
    //    connect(buttonBox, &QDialogButtonBox::rejected, this, &OpenUrlWithConfigureDialog::reject);
}

OpenUrlWithConfigureCreateDialog::~OpenUrlWithConfigureCreateDialog()
{
}
