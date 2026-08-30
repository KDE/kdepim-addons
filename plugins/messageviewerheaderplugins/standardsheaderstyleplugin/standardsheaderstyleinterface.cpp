/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "standardsheaderstyleinterface.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <KToggleAction>
using namespace Qt::Literals::StringLiterals;

using namespace MessageViewer;
StandardsHeaderStyleInterface::StandardsHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
}

StandardsHeaderStyleInterface::~StandardsHeaderStyleInterface() = default;

void StandardsHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    auto act = new KToggleAction(i18nc("View->headers->", "&Standard Headers"), this);
    ac->addAction(u"view_headers_standard"_s, act);
    connect(act, &KToggleAction::triggered, this, &StandardsHeaderStyleInterface::slotStyleChanged);
    addHelpTextAction(act, i18n("Show standard list of message headers"));
    mAction.append(act);
    addActionToMenu(menu, actionGroup);
}

void StandardsHeaderStyleInterface::activateAction()
{
    mAction.at(0)->setChecked(true);
}

#include "moc_standardsheaderstyleinterface.cpp"
