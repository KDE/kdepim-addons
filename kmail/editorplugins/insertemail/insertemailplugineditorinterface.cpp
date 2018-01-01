/*
   Copyright (C) 2017-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
    MessageComposer::ActionType type(action, MessageComposer::ActionType::Edit);
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
    richTextEditor()->insertPlainText(lst.join(QLatin1Char(' ')));
}
