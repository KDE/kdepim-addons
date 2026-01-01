/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "longheaderstyleinterface.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <KToggleAction>

using namespace MessageViewer;
LongHeaderStyleInterface::LongHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
}

LongHeaderStyleInterface::~LongHeaderStyleInterface() = default;

void LongHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    auto act = new KToggleAction(i18nc("View->headers->", "&Long Headers"), this);
    ac->addAction(QStringLiteral("view_headers_long"), act);
    connect(act, &KToggleAction::triggered, this, &LongHeaderStyleInterface::slotStyleChanged);
    addHelpTextAction(act, i18n("Show long list of message headers"));
    mAction.append(act);
    addActionToMenu(menu, actionGroup);
}

void LongHeaderStyleInterface::activateAction()
{
    mAction.at(0)->setChecked(true);
}

#include "moc_longheaderstyleinterface.cpp"
