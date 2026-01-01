/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichataddressbookpluginwidget.h"
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateToolPluginConfigureWidget>
using namespace Qt::Literals::StringLiterals;
KAIChatAddressBookPluginWidget::KAIChatAddressBookPluginWidget(TextAutoGenerateText::TextAutoGenerateTextToolPlugin *plugin, QWidget *parent)
    : QWidget{parent}
    , mConfigureWidget(new TextAutoGenerateText::TextAutoGenerateToolPluginConfigureWidget(plugin, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    mConfigureWidget->setObjectName(u"mConfigureWidget"_s);
    mainLayout->addWidget(mConfigureWidget);
    mainLayout->addStretch(1);
}

KAIChatAddressBookPluginWidget::~KAIChatAddressBookPluginWidget() = default;

#include "moc_kaichataddressbookpluginwidget.cpp"
