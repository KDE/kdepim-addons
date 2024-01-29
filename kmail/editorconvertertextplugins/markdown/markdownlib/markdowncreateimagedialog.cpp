/*
    SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreateimagedialog.h"
#include "markdowncreateimagewidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
static const char myMarkdownCreateImageDialogGroupName[] = "MarkdownCreateImageDialog";
}

MarkdownCreateImageDialog::MarkdownCreateImageDialog(QWidget *parent)
    : QDialog(parent)
    , mMarkdownCreateImageWidget(new MarkdownCreateImageWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Image"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));

    mMarkdownCreateImageWidget->setObjectName(QLatin1StringView("markdowncreateimagewidget"));

    mainLayout->addWidget(mMarkdownCreateImageWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName(QLatin1StringView("buttonbox"));
    mOkButton = box->button(QDialogButtonBox::Ok);
    mOkButton->setObjectName(QLatin1StringView("okbutton"));
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
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myMarkdownCreateImageDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void MarkdownCreateImageDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(300, 200));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myMarkdownCreateImageDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

#include "moc_markdowncreateimagedialog.cpp"
