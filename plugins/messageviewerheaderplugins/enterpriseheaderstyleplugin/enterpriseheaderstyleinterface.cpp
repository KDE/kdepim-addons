/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "enterpriseheaderstyleinterface.h"
#include <KToggleAction>
#include <KLocalizedString>
#include <KActionCollection>
using namespace MessageViewer;
EnterpriseHeaderStyleInterface::EnterpriseHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent)
    : MessageViewer::HeaderStyleInterface(plugin, parent)
{
}

EnterpriseHeaderStyleInterface::~EnterpriseHeaderStyleInterface()
{
}

void EnterpriseHeaderStyleInterface::createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac)
{
    KToggleAction *act = new KToggleAction(i18nc("View->headers->", "&Enterprise Headers"), this);
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
