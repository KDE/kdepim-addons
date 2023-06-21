/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugintranslatorinterface.h"
#include <TextTranslator/TranslatorWidget>

#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>
#include <QIcon>
#include <QLayout>

using namespace MessageViewer;

ViewerPluginTranslatorInterface::ViewerPluginTranslatorInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    createAction(ac);
}

ViewerPluginTranslatorInterface::~ViewerPluginTranslatorInterface() = default;

void ViewerPluginTranslatorInterface::setText(const QString &text)
{
    widget()->setTextToTranslate(text);
}

QList<QAction *> ViewerPluginTranslatorInterface::actions() const
{
    return mAction;
}

void ViewerPluginTranslatorInterface::showWidget()
{
    widget()->show();
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginTranslatorInterface::featureTypes() const
{
    return NeedSelection;
}

void ViewerPluginTranslatorInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        auto act = new QAction(i18n("Translate..."), this);
        ac->setDefaultShortcut(act, QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_T));
        act->setIcon(QIcon::fromTheme(QStringLiteral("preferences-desktop-locale")));
        ac->addAction(QStringLiteral("translate_text"), act);
        connect(act, &QAction::triggered, this, &ViewerPluginTranslatorInterface::slotActivatePlugin);
        mAction.append(act);
    }
}

TextTranslator::TranslatorWidget *ViewerPluginTranslatorInterface::widget()
{
    if (!mTranslatorWidget) {
        auto parentWidget = static_cast<QWidget *>(parent());
        mTranslatorWidget = new TextTranslator::TranslatorWidget(parentWidget);
        mTranslatorWidget->setObjectName(QStringLiteral("translatorwidget"));
        parentWidget->layout()->addWidget(mTranslatorWidget);
        mTranslatorWidget->hide();
    }
    return mTranslatorWidget;
}

#include "moc_viewerplugintranslatorinterface.cpp"
