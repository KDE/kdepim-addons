/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerplugineditor.h"
#include "externalcomposerplugineditorinterface.h"
#include "externalcomposerconfiguredialog.h"
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
    ExternalComposerPluginEditorInterface *interface = new ExternalComposerPluginEditorInterface(parent);
    return interface;
}

bool ExternalComposerPluginEditor::hasConfigureDialog() const
{
    return true;
}

void ExternalComposerPluginEditor::showConfigureDialog(QWidget *parent)
{
    QPointer<ExternalComposerConfigureDialog> dlg = new ExternalComposerConfigureDialog(parent);
    dlg->exec();
    delete dlg;
}

#include "externalcomposerplugineditor.moc"
