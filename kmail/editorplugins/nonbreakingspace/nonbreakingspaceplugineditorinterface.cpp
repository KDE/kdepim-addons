/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "nonbreakingspaceplugineditorinterface.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <KPIMTextEdit/RichTextEditor>
#include <QAction>

NonBreakingSpacePluginEditorInterface::NonBreakingSpacePluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

NonBreakingSpacePluginEditorInterface::~NonBreakingSpacePluginEditorInterface() = default;

void NonBreakingSpacePluginEditorInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18n("Insert Non Breaking Space"), this);
    ac->addAction(QStringLiteral("insert_non_breaking_space"), action);
    ac->setDefaultShortcut(action, Qt::CTRL | Qt::Key_Space);
    connect(action, &QAction::triggered, this, &NonBreakingSpacePluginEditorInterface::slotActivated);
    MessageComposer::PluginActionType type(action, MessageComposer::PluginActionType::Insert);
    setActionType(type);
}

void NonBreakingSpacePluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void NonBreakingSpacePluginEditorInterface::exec()
{
    richTextEditor()->insertPlainText(QChar(0x000A0));
}
