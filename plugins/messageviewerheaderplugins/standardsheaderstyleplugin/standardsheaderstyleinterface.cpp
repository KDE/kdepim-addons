/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "standardsheaderstyleinterface.h"
#include <KToggleAction>
#include <KLocalizedString>
#include <KActionCollection>

using namespace MessageViewer;
StandardsHeaderStyleInterface::StandardsHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
}

StandardsHeaderStyleInterface::~StandardsHeaderStyleInterface()
{
}

void StandardsHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    KToggleAction *act = new KToggleAction(i18nc("View->headers->", "&Standard Headers"), this);
    ac->addAction(QStringLiteral("view_headers_standard"), act);
    connect(act, &KToggleAction::triggered, this, &StandardsHeaderStyleInterface::slotStyleChanged);
    addHelpTextAction(act, i18n("Show standard list of message headers"));
    mAction.append(act);
    addActionToMenu(menu, actionGroup);
}

void StandardsHeaderStyleInterface::activateAction()
{
    mAction.at(0)->setChecked(true);
}
