/*
   Copyright (C) 2018-2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
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
