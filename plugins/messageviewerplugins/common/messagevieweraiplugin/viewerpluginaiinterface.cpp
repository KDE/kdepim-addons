/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginaiinterface.h"
#include "viewerpluginaiwidget.h"

#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>
#include <QIcon>
#include <QLayout>

using namespace MessageViewer;

ViewerPluginAIInterface::ViewerPluginAIInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    createAction(ac);
}

ViewerPluginAIInterface::~ViewerPluginAIInterface() = default;

void ViewerPluginAIInterface::setText(const QString &text)
{
    // widget()->setTextToTranslate(text);
}

QList<QAction *> ViewerPluginAIInterface::actions() const
{
    return mAction;
}

void ViewerPluginAIInterface::showWidget()
{
    widget()->show();
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginAIInterface::featureTypes() const
{
    return NeedSelection;
}

void ViewerPluginAIInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        auto act = new QAction(i18nc("@action", "Ask AI…"), this);
        // ac->setDefaultShortcut(act, QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_T));
        ac->addAction(QStringLiteral("ask_ai_text"), act);
        connect(act, &QAction::triggered, this, &ViewerPluginAIInterface::slotActivatePlugin);
        mAction.append(act);
    }
}

ViewerPluginAIWidget *ViewerPluginAIInterface::widget()
{
    if (!mAiWidget) {
        auto parentWidget = static_cast<QWidget *>(parent());
        mAiWidget = new ViewerPluginAIWidget(parentWidget);
        mAiWidget->setObjectName(QLatin1StringView("mAiWidget"));
        parentWidget->layout()->addWidget(mAiWidget);
        mAiWidget->hide();
    }
    return mAiWidget;
}

#include "moc_viewerpluginaiinterface.cpp"
