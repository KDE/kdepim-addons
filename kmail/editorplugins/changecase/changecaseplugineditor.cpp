/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "changecaseplugineditor.h"
#include "changecaseplugineditorinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(ChangeCasePluginEditor, "kmail_changecaseeditorplugin.json")

ChangeCasePluginEditor::ChangeCasePluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

ChangeCasePluginEditor::~ChangeCasePluginEditor() = default;

bool ChangeCasePluginEditor::hasPopupMenuSupport() const
{
    return true;
}

MessageComposer::PluginEditorInterface *ChangeCasePluginEditor::createInterface(QObject *parent)
{
    return new ChangeCasePluginEditorInterface(parent);
}

#include "changecaseplugineditor.moc"

#include "moc_changecaseplugineditor.cpp"
