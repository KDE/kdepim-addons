/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichataddressbookplugindialog.h"
#include "kaichataddressbookpluginwidget.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPlugin>
using namespace Qt::Literals::StringLiterals;
KAIChatAddressBookPluginDialog::KAIChatAddressBookPluginDialog(TextAutoGenerateText::TextAutoGenerateTextToolPlugin *plugin, QWidget *parent)
    : QDialog(parent)
    , mAddressbookToolPluginWidget(new KAIChatAddressBookPluginWidget(plugin, this))
{
    setWindowTitle(plugin ? plugin->displayName() : i18n("Configure Addressbool Tool Plugin"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mAddressbookToolPluginWidget->setObjectName(u"mCurrentDateTimeToolPluginWidget"_s);
    mainLayout->addWidget(mAddressbookToolPluginWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &KAIChatAddressBookPluginDialog::reject);
}

KAIChatAddressBookPluginDialog::~KAIChatAddressBookPluginDialog() = default;

#include "moc_kaichataddressbookplugindialog.cpp"
