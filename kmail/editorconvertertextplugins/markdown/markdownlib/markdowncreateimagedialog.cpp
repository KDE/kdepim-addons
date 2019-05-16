/*
    Copyright (C) 2019 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "markdowncreateimagedialog.h"
#include "markdowncreateimagewidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <KConfigGroup>
#include <KSharedConfig>

MarkdownCreateImageDialog::MarkdownCreateImageDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(i18n("Add Image"));
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mMarkdownCreateImageWidget = new MarkdownCreateImageWidget(this);
    mMarkdownCreateImageWidget->setObjectName(QStringLiteral("markdowncreateimagewidget"));

    mainLayout->addWidget(mMarkdownCreateImageWidget);

    QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
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
    KConfigGroup group(KSharedConfig::openConfig(), "MarkdownCreateImageDialog");
    group.writeEntry("Size", size());
}

void MarkdownCreateImageDialog::readConfig()
{
    KConfigGroup group(KSharedConfig::openConfig(), "MarkdownCreateImageDialog");
    const QSize sizeDialog = group.readEntry("Size", QSize(300, 200));
    if (sizeDialog.isValid()) {
        resize(sizeDialog);
    }
}
