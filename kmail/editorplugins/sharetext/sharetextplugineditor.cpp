/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sharetextplugineditor.h"
#include "sharetextplugineditorinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(ShareTextPluginEditor, "kmail_sharetexteditorplugin.json")

ShareTextPluginEditor::ShareTextPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

ShareTextPluginEditor::~ShareTextPluginEditor()
{
}

bool ShareTextPluginEditor::hasPopupMenuSupport() const
{
    return false;
}

MessageComposer::PluginEditorInterface *ShareTextPluginEditor::createInterface(QObject *parent)
{
    return new ShareTextPluginEditorInterface(parent);
}

#include "sharetextplugineditor.moc"
