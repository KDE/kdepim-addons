/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "kaichatcalendarplugindialog.h"
#include "kaichatcalendarpluginwidget.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <TextAutoGenerateText/TextAutoGenerateTextToolPlugin>
using namespace Qt::Literals::StringLiterals;
KAIChatCalendarPluginDialog::KAIChatCalendarPluginDialog(TextAutoGenerateText::TextAutoGenerateTextToolPlugin *plugin, QWidget *parent)
    : QDialog(parent)
    , mCalendarToolPluginWidget(new KAIChatCalendarPluginWidget(plugin, this))
{
    setWindowTitle(plugin ? plugin->displayName() : i18n("Configure Calendar Tool Plugin"));

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);

    mCalendarToolPluginWidget->setObjectName(u"mCurrentDateTimeToolPluginWidget"_s);
    mainLayout->addWidget(mCalendarToolPluginWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Close, this);
    button->setObjectName(u"button"_s);
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &KAIChatCalendarPluginDialog::reject);
}

KAIChatCalendarPluginDialog::~KAIChatCalendarPluginDialog() = default;

#include "moc_kaichatcalendarplugindialog.cpp"
