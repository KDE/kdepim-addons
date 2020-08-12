/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertemailplugineditorinterface.h"
#include "selectmaildialog.h"
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

InsertEmailPluginEditorInterface::InsertEmailPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

InsertEmailPluginEditorInterface::~InsertEmailPluginEditorInterface()
{
}

void InsertEmailPluginEditorInterface::createAction(KActionCollection *ac)
{
    QAction *action = new QAction(i18n("Insert Email..."), this);
    ac->addAction(QStringLiteral("insert_email"), action);
    connect(action, &QAction::triggered, this, &InsertEmailPluginEditorInterface::slotActivated);
    MessageComposer::PluginActionType type(action, MessageComposer::PluginActionType::Edit);
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
    Q_EMIT insertText(lst.join(QLatin1Char(' ')));
}
