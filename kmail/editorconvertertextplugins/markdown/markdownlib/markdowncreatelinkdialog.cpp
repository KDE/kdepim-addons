/*
    SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

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
#include <TextAddonsWidgets/LoadDialogSizeUtils>
using namespace Qt::Literals::StringLiterals;

namespace
{
const char myMarkdownCreateLinkDialogGroupName[] = "MarkdownCreateLinkDialog";
}
MarkdownCreateLinkDialog::MarkdownCreateLinkDialog(QWidget *parent)
    : QDialog(parent)
    , mMarkdownCreateLinkWidget(new MarkdownCreateLinkWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Add Link"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainlayout"_L1);

    mMarkdownCreateLinkWidget->setObjectName("markdowncreatelinkwidget"_L1);

    mainLayout->addWidget(mMarkdownCreateLinkWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    box->setObjectName("buttonbox"_L1);
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &MarkdownCreateLinkDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &MarkdownCreateLinkDialog::reject);

    mOkButton = box->button(QDialogButtonBox::Ok);
    mOkButton->setObjectName("okbutton"_L1);
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
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myMarkdownCreateLinkDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void MarkdownCreateLinkDialog::readConfig()
{
    create(); // ensure a window is created
    TextAddonsWidgets::LoadDialogSizeUtils::loadDialogSizeScaled(this, QLatin1StringView(myMarkdownCreateLinkDialogGroupName), 300, 200);
}

#include "moc_markdowncreatelinkdialog.cpp"
