/*
    SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreateimagedialog.h"
#include "markdowncreateimagewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

MarkdownCreateImageDialog::MarkdownCreateImageDialog(QWidget *parent)
    : QDialog(parent)
    , mMarkdownCreateImageWidget(new MarkdownCreateImageWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Image"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mMarkdownCreateImageWidget->setObjectName(QStringLiteral("markdowncreateimagewidget"));

    mainLayout->addWidget(mMarkdownCreateImageWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("buttonbox"));
    mOkButton = box->button(QDialogButtonBox::Ok);
    mOkButton->setObjectName(QStringLiteral("okbutton"));
    mOkButton->setEnabled(false);
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &MarkdownCreateImageDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &MarkdownCreateImageDialog::reject);
    connect(mMarkdownCreateImageWidget, &MarkdownCreateImageWidget::enabledOkButton, this, &MarkdownCreateImageDialog::slotEnabledOkButton);
    readConfig();
}

MarkdownCreateImageDialog::~MarkdownCreateImageDialog()
{
    writeConfig();
}

void MarkdownCreateImageDialog::slotEnabledOkButton(bool enabled)
{
    mOkButton->setEnabled(enabled);
}

QString MarkdownCreateImageDialog::linkStr() const
{
    return mMarkdownCreateImageWidget->linkStr();
}

void MarkdownCreateImageDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "MarkdownCreateImageDialog");
    group.writeEntry("Size", size());
}

void MarkdownCreateImageDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), "MarkdownCreateImageDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(300, 200));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
