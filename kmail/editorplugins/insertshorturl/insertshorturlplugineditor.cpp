/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlplugineditor.h"
#include "insertshorturlplugineditorinterface.h"
#include "insertshorturlconfiguredialog.h"
#include <KPluginFactory>
#include <QPointer>

K_PLUGIN_CLASS_WITH_JSON(InsertShorturlPluginEditor, "kmail_insertshorturleditorplugin.json")

InsertShorturlPluginEditor::InsertShorturlPluginEditor(QObject *parent, const QList<QVariant> &)
    : MessageComposer::PluginEditor(parent)
{
}

InsertShorturlPluginEditor::~InsertShorturlPluginEditor()
{
}

MessageComposer::PluginEditorInterface *InsertShorturlPluginEditor::createInterface(QObject *parent)
{
    InsertShorturlPluginEditorInterface *interface = new InsertShorturlPluginEditorInterface(parent);
    connect(this, &InsertShorturlPluginEditor::configChanged, interface, &InsertShorturlPluginEditorInterface::loadEngine);
    return interface;
}

bool InsertShorturlPluginEditor::hasPopupMenuSupport() const
{
    return true;
}

bool InsertShorturlPluginEditor::hasConfigureDialog() const
{
    return true;
}

void InsertShorturlPluginEditor::showConfigureDialog(QWidget *parent)
{
    QPointer<InsertShorturlConfigureDialog> dlg = new InsertShorturlConfigureDialog(parent);
    if (dlg->exec()) {
        Q_EMIT configChanged();
    }
    delete dlg;
}

#include "insertshorturlplugineditor.moc"
