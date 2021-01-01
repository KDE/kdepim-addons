/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionplugineditorinterface.h"
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <KActionMenu>

AutoCorrectionPluginEditorInterface::AutoCorrectionPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

AutoCorrectionPluginEditorInterface::~AutoCorrectionPluginEditorInterface()
{
}

void AutoCorrectionPluginEditorInterface::createAction(KActionCollection *ac)
{
    KActionMenu *menu = new KActionMenu(i18n("Autocorrect Text"), this);
    ac->addAction(QStringLiteral("autocorrect_tool"), menu);
    MessageComposer::PluginActionType type(menu, MessageComposer::PluginActionType::Tools);
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
