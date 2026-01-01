/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertemailplugineditorinterface.h"
using namespace Qt::Literals::StringLiterals;

#include "selectmaildialog.h"
#include <KActionCollection>
#include <KLocalizedString>
#include <QAction>
#include <TextCustomEditor/RichTextEditor>

InsertEmailPluginEditorInterface::InsertEmailPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

InsertEmailPluginEditorInterface::~InsertEmailPluginEditorInterface() = default;

void InsertEmailPluginEditorInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18nc("@action", "Insert Email…"), this);
    ac->addAction(u"insert_email"_s, action);
    connect(action, &QAction::triggered, this, &InsertEmailPluginEditorInterface::slotActivated);
    MessageComposer::PluginActionType type(action, MessageComposer::PluginActionType::Insert);
    setActionType(type);
}

void InsertEmailPluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void InsertEmailPluginEditorInterface::exec()
{
    if (!mSelectMailDialog) {
        mSelectMailDialog = new SelectMailDialog(parentWidget());
        connect(mSelectMailDialog.data(), &SelectMailDialog::emailSelected, this, &InsertEmailPluginEditorInterface::slotEmailSelected);
    }
    mSelectMailDialog->show();
}

void InsertEmailPluginEditorInterface::slotEmailSelected(const QStringList &lst)
{
    Q_EMIT insertText(lst.join(u' '));
}

#include "moc_insertemailplugineditorinterface.cpp"
