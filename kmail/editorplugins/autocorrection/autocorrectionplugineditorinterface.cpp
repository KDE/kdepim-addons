/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autocorrectionplugineditorinterface.h"
#include <KActionCollection>
#include <KActionMenu>
#include <KLocalizedString>
#include <QAction>
#include <TextCustomEditor/RichTextEditor>

AutoCorrectionPluginEditorInterface::AutoCorrectionPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

AutoCorrectionPluginEditorInterface::~AutoCorrectionPluginEditorInterface() = default;

void AutoCorrectionPluginEditorInterface::createAction(KActionCollection *ac)
{
    auto menu = new KActionMenu(i18n("Autocorrect Text"), this);
    ac->addAction(QStringLiteral("autocorrect_tool"), menu);
    MessageComposer::PluginActionType type(menu, MessageComposer::PluginActionType::Tools);
    setActionType(type);

    auto action = new QAction(i18nc("@action", "Autocorrect Full Text"), this);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, &AutoCorrectionPluginEditorInterface::slotAutoCorrectAllText);

    action = new QAction(i18nc("@action", "Autocorrect Selected Text"), this);
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

#include "moc_autocorrectionplugineditorinterface.cpp"
