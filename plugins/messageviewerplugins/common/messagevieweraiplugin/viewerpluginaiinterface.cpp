/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerpluginaiinterface.h"
// #include <TextTranslator/TranslatorWidget>

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
    // widget()->show();
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginAIInterface::featureTypes() const
{
    return NeedSelection;
}

void ViewerPluginAIInterface::createAction(KActionCollection *ac)
{
#if 0
    if (ac) {
        auto act = new QAction(i18nc("@action", "Translate…"), this);
        ac->setDefaultShortcut(act, QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_T));
        act->setIcon(QIcon::fromTheme(QStringLiteral("preferences-desktop-locale")));
        ac->addAction(QStringLiteral("translate_text"), act);
        connect(act, &QAction::triggered, this, &ViewerPluginAIInterface::slotActivatePlugin);
        mAction.append(act);
    }
#endif
}

#if 0
TextTranslator::TranslatorWidget *ViewerPluginAIInterface::widget()
{
    if (!mTranslatorWidget) {
        auto parentWidget = static_cast<QWidget *>(parent());
        mTranslatorWidget = new TextTranslator::TranslatorWidget(parentWidget);
        mTranslatorWidget->setObjectName(QLatin1StringView("translatorwidget"));
        parentWidget->layout()->addWidget(mTranslatorWidget);
        mTranslatorWidget->hide();
    }
    return mTranslatorWidget;
}

#endif
#include "moc_viewerpluginaiinterface.cpp"
