/*
   SPDX-FileCopyrightText: 2017-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerplugineditor.h"
#include "externalcomposerconfiguredialog.h"
#include "externalcomposerplugineditorinterface.h"
#include <KPluginFactory>

K_PLUGIN_CLASS_WITH_JSON(ExternalComposerPluginEditor, "kmail_externalcomposereditorplugin.json")

ExternalComposerPluginEditor::ExternalComposerPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditorInit(parent)
{
}

ExternalComposerPluginEditor::~ExternalComposerPluginEditor()
{
}

MessageComposer::PluginEditorInitInterface *ExternalComposerPluginEditor::createInterface(QObject *parent)
{
    auto *interface = new ExternalComposerPluginEditorInterface(parent);
    return interface;
}

bool ExternalComposerPluginEditor::hasConfigureDialog() const
{
    return true;
}

void ExternalComposerPluginEditor::showConfigureDialog(QWidget *parent)
{
    ExternalComposerConfigureDialog dlg(parent);
    dlg.exec();
}

#include "externalcomposerplugineditor.moc"
