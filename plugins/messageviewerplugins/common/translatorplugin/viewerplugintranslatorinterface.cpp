/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugintranslatorinterface.h"
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
#include <TextTranslator/TranslatorWidget>
#else
#include <PimCommonTextTranslator/TranslatorWidget>
#endif

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

#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
TextTranslator::TranslatorWidget *ViewerPluginTranslatorInterface::widget()
#else
PimCommonTextTranslator::TranslatorWidget *ViewerPluginTranslatorInterface::widget()
#endif
{
    if (!mTranslatorWidget) {
        auto parentWidget = static_cast<QWidget *>(parent());
#ifdef HAVE_KTEXTADDONS_TEXT_SUPPORT
        mTranslatorWidget = new TextTranslator::TranslatorWidget(parentWidget);
#else
        mTranslatorWidget = new PimCommonTextTranslator::TranslatorWidget(parentWidget);
#endif
        mTranslatorWidget->setObjectName(QStringLiteral("translatorwidget"));
        parentWidget->layout()->addWidget(mTranslatorWidget);
        mTranslatorWidget->hide();
    }
    return mTranslatorWidget;
}
