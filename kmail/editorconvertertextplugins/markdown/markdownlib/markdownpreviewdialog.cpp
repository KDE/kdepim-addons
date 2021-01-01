/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownpreviewdialog.h"
#include "markdownpreviewwidget.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <KConfigGroup>
#include <KSharedConfig>
#include <KLocalizedString>

MarkdownPreviewDialog::MarkdownPreviewDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Markdown Rendering Preview"));
    setAttribute(Qt::WA_DeleteOnClose);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mPreviewWidget = new MarkdownPreviewWidget(this);
    mPreviewWidget->setObjectName(QStringLiteral("previewwidget"));
    mainLayout->addWidget(mPreviewWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    buttonBox->setObjectName(QStringLiteral("buttonbox"));
    mainLayout->addWidget(buttonBox);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &MarkdownPreviewDialog::reject);
    readConfig();
}

MarkdownPreviewDialog::~MarkdownPreviewDialog()
{
    writeConfig();
}

void MarkdownPreviewDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "MarkdownPreviewDialog");
    group.writeEntry("Size", size());
}

void MarkdownPreviewDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "MarkdownPreviewDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(500, 300));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}

void MarkdownPreviewDialog::setText(const QString &str)
{
    mPreviewWidget->slotUpdatePreview(str);
}

void MarkdownPreviewDialog::setConverterSettings(bool enableEmbeddedLabel, bool enableExtraDefinitionLists)
{
    mPreviewWidget->setConverterSettings(enableEmbeddedLabel, enableExtraDefinitionLists);
}
