/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorconfiguredialog.h"
#include "translatorconfigurewidget.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

TranslatorConfigureDialog::TranslatorConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mTranslatorConfigureWidget(new TranslatorConfigureWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Configure Translator"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mTranslatorConfigureWidget->setObjectName(QStringLiteral("mTranslatorConfigureWidget"));

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    mainLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &TranslatorConfigureDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &TranslatorConfigureDialog::reject);
}

TranslatorConfigureDialog::~TranslatorConfigureDialog() = default;
