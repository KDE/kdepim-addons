/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlconfiguredialog.h"
#include "insertshorturlconfigurewidget.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

InsertShorturlConfigureDialog::InsertShorturlConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , mInsertShortUrlWidget(new InsertShorturlConfigureWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);

    mInsertShortUrlWidget->setObjectName("insertshorturlwidget"_L1);
    mainLayout->addWidget(mInsertShortUrlWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    buttonBox->setObjectName("buttonbox"_L1);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &InsertShorturlConfigureDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &InsertShorturlConfigureDialog::reject);
    mainLayout->addWidget(buttonBox);
}

InsertShorturlConfigureDialog::~InsertShorturlConfigureDialog() = default;

void InsertShorturlConfigureDialog::accept()
{
    mInsertShortUrlWidget->writeConfig();
    QDialog::accept();
}

#include "moc_insertshorturlconfiguredialog.cpp"
