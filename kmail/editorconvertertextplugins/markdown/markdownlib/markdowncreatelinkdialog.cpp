/*
    SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdowncreatelinkdialog.h"
#include "markdowncreatelinkwidget.h"
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
static const char myMarkdownCreateLinkDialogGroupName[] = "MarkdownCreateLinkDialog";
}
MarkdownCreateLinkDialog::MarkdownCreateLinkDialog(QWidget *parent)
    : QDialog(parent)
    , mMarkdownCreateLinkWidget(new MarkdownCreateLinkWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Link"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));

    mMarkdownCreateLinkWidget->setObjectName(QStringLiteral("markdowncreatelinkwidget"));

    mainLayout->addWidget(mMarkdownCreateLinkWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
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
    KConfigGroup group(KSharedConfig::openStateConfig(), myMarkdownCreateLinkDialogGroupName);
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void MarkdownCreateLinkDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(300, 200));
    KConfigGroup group(KSharedConfig::openStateConfig(), myMarkdownCreateLinkDialogGroupName);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}
