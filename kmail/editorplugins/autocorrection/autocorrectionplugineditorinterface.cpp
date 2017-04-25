/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "autocorrectionplugineditorinterface.h"
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <KActionMenu>

AutoCorrectionPluginEditorInterface::AutoCorrectionPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
    , mSelectedText(false)
{
}

AutoCorrectionPluginEditorInterface::~AutoCorrectionPluginEditorInterface()
{
}

void AutoCorrectionPluginEditorInterface::createAction(KActionCollection *ac)
{
    KActionMenu *menu = new KActionMenu(i18n("Autocorrect Text"), this);
    ac->addAction(QStringLiteral("autocorrect_tool"), menu);
    MessageComposer::ActionType type(menu, MessageComposer::ActionType::Tools);
    setActionType(type);

    QAction *action = new QAction(i18n("Autocorrect Full Text"), this);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &AutoCorrectionPluginEditorInterface::slotAutoCorrectAllText);

    action = new QAction(i18n("Autocorrect Selected Text"), this);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &AutoCorrectionPluginEditorInterface::slotAutoCorrectSelectedText);
}

void AutoCorrectionPluginEditorInterface::slotAutoCorrectSelectedText()
{
    mSelectedText = true;
    Q_EMIT emitPluginActivated(this);
}

void AutoCorrectionPluginEditorInterface::slotAutoCorrectAllText()
{
    mSelectedText = false;
    Q_EMIT emitPluginActivated(this);
}

void AutoCorrectionPluginEditorInterface::exec()
{
    richTextEditor()->forceAutoCorrection(mSelectedText);
}
