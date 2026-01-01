/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "briefheaderstyleinterface.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <KToggleAction>

using namespace MessageViewer;
BriefHeaderStyleInterface::BriefHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
}

BriefHeaderStyleInterface::~BriefHeaderStyleInterface() = default;

void BriefHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    auto act = new KToggleAction(i18nc("View->headers->", "&Brief Headers"), this);
    ac->addAction(QStringLiteral("view_headers_brief"), act);
    connect(act, &KToggleAction::triggered, this, &BriefHeaderStyleInterface::slotStyleChanged);
    addHelpTextAction(act, i18n("Show brief list of message headers"));
    mAction.append(act);
    addActionToMenu(menu, actionGroup);
}

void BriefHeaderStyleInterface::activateAction()
{
    mAction.at(0)->setChecked(true);
}

#include "moc_briefheaderstyleinterface.cpp"
