/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "fancyheaderstyleinterface.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <KToggleAction>

using namespace MessageViewer;
FancyHeaderStyleInterface::FancyHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
}

FancyHeaderStyleInterface::~FancyHeaderStyleInterface() = default;

void FancyHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    auto act = new KToggleAction(i18nc("View->headers->", "&Fancy Headers"), this);
    ac->addAction(QStringLiteral("view_headers_fancy"), act);
    connect(act, &KToggleAction::triggered, this, &FancyHeaderStyleInterface::slotStyleChanged);
    addHelpTextAction(act, i18n("Show the list of headers in a fancy format"));
    mAction.append(act);
    addActionToMenu(menu, actionGroup);
}

void FancyHeaderStyleInterface::activateAction()
{
    mAction.at(0)->setChecked(true);
}

#include "moc_fancyheaderstyleinterface.cpp"
