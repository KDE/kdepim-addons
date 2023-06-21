/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "enterpriseheaderstyleinterface.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <KToggleAction>
using namespace MessageViewer;
EnterpriseHeaderStyleInterface::EnterpriseHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
}

EnterpriseHeaderStyleInterface::~EnterpriseHeaderStyleInterface() = default;

void EnterpriseHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    auto act = new KToggleAction(i18nc("View->headers->", "&Enterprise Headers"), this);
    ac->addAction(QStringLiteral("view_headers_enterprise"), act);
    connect(act, &KToggleAction::triggered, this, &EnterpriseHeaderStyleInterface::slotStyleChanged);
    addHelpTextAction(act, i18n("Show the list of headers in Enterprise style"));
    mAction.append(act);
    addActionToMenu(menu, actionGroup);
}

void EnterpriseHeaderStyleInterface::activateAction()
{
    mAction.at(0)->setChecked(true);
}

#include "moc_enterpriseheaderstyleinterface.cpp"
