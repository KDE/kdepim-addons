/*
    SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreatelinkdialog.h"
#include "markdowncreatelinkwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

MarkdownCreateLinkDialog::MarkdownCreateLinkDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Add Link"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mMarkdownCreateLinkWidget = new MarkdownCreateLinkWidget(this);
    mMarkdownCreateLinkWidget->setObjectName(QStringLiteral("markdowncreatelinkwidget"));

    mainLayout->addWidget(mMarkdownCreateLinkWidget);

    QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QStringLiteral("buttonbox"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &MarkdownCreateLinkDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &MarkdownCreateLinkDialog::reject);

    mOkButton = box->button(QDialogButtonBox::Ok);
    mOkButton->setObjectName(QStringLiteral("okbutton"));
    mOkButton->setEnabled(false);
    connect(mMarkdownCreateLinkWidget, &MarkdownCreateLinkWidget::enabledOkButton, this, &MarkdownCreateLinkDialog::slotEnabledOkButton);
    readConfig();
}

MarkdownCreateLinkDialog::~MarkdownCreateLinkDialog()
{
    writeConfig();
}

void MarkdownCreateLinkDialog::slotEnabledOkButton(bool enabled)
{
    mOkButton->setEnabled(enabled);
}

QString MarkdownCreateLinkDialog::linkStr() const
{
    return mMarkdownCreateLinkWidget->linkStr();
}

void MarkdownCreateLinkDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "MarkdownCreateLinkDialog");
    group.writeEntry("Size", size());
}

void MarkdownCreateLinkDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "MarkdownCreateLinkDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(300, 200));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
