/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "aitooltextplugineditorinterface.h"
using namespace Qt::Literals::StringLiterals;

#include "textautogeneratetext_version.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>
#include <TextAutoGenerateText/TextAutoGenerateManager>
#include <TextAutoGenerateText/TextAutoGenerateQuickAskDialog>

AIToolTextPluginEditorInterface::AIToolTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

AIToolTextPluginEditorInterface::~AIToolTextPluginEditorInterface() = default;

void AIToolTextPluginEditorInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18nc("@action", "Open AI Chat"), this);
    ac->addAction(u"open_ai_chat"_s, action);
    connect(action, &QAction::triggered, this, &AIToolTextPluginEditorInterface::slotActivated);
    MessageComposer::PluginActionType type(action, MessageComposer::PluginActionType::Tools);
    setActionType(type);
}

void AIToolTextPluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void AIToolTextPluginEditorInterface::exec()
{
    auto *manager = new TextAutoGenerateText::TextAutoGenerateManager(this);
    auto d = new TextAutoGenerateText::TextAutoGenerateQuickAskDialog(manager, parentWidget());
    d->setAttribute(Qt::WA_DeleteOnClose);
    d->show();
}

#include "moc_aitooltextplugineditorinterface.cpp"
