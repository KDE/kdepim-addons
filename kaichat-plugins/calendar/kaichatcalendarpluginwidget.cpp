/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichatcalendarpluginwidget.h"
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateToolPluginConfigureWidget>
using namespace Qt::Literals::StringLiterals;
KAIChatCalendarPluginWidget::KAIChatCalendarPluginWidget(TextAutoGenerateText::TextAutoGenerateTextToolPlugin *plugin, QWidget *parent)
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

KAIChatCalendarPluginWidget::~KAIChatCalendarPluginWidget() = default;

#include "moc_kaichatcalendarpluginwidget.cpp"
