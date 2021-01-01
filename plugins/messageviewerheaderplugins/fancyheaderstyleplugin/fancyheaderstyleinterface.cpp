/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "fancyheaderstyleinterface.h"
#include <KToggleAction>
#include <KLocalizedString>
#include <KActionCollection>

using namespace MessageViewer;
FancyHeaderStyleInterface::FancyHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
}

FancyHeaderStyleInterface::~FancyHeaderStyleInterface()
{
}

void FancyHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    KToggleAction *act = new KToggleAction(i18nc("View->headers->", "&Fancy Headers"), this);
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
