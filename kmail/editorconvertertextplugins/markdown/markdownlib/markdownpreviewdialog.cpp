/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownpreviewdialog.h"
#include "markdownpreviewwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
static const char myMarkdownPreviewDialogGroupName[] = "MarkdownPreviewDialog";
}
MarkdownPreviewDialog::MarkdownPreviewDialog(QWidget *parent)
    : QDialog(parent)
    , mPreviewWidget(new MarkdownPreviewWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Markdown Rendering Preview"));
    setAttribute(Qt::WA_DeleteOnClose);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mPreviewWidget->setObjectName(QStringLiteral("previewwidget"));
    mainLayout->addWidget(mPreviewWidget);

    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
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
    KConfigGroup group(KSharedConfig::openStateConfig(), myMarkdownPreviewDialogGroupName);
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void MarkdownPreviewDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(500, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), myMarkdownPreviewDialogGroupName);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void MarkdownPreviewDialog::setText(const QString &str)
{
    mPreviewWidget->slotUpdatePreview(str);
}

void MarkdownPreviewDialog::setConverterSettings(bool enableEmbeddedLabel, bool enableExtraDefinitionLists)
{
    mPreviewWidget->setConverterSettings(enableEmbeddedLabel, enableExtraDefinitionLists);
}
