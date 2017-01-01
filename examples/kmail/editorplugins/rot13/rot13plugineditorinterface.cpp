/*
  Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "rot13plugineditorinterface.h"
#include "rot13job.h"
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>

Rot13PluginEditorInterface::Rot13PluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{

}

Rot13PluginEditorInterface::~Rot13PluginEditorInterface()
{

}

void Rot13PluginEditorInterface::createAction(KActionCollection *ac)
{
    QAction *action = new QAction(i18n("Rot13 converter"), this);
    ac->addAction(QStringLiteral("rot13converter"), action);
    connect(action, &QAction::triggered, this, &Rot13PluginEditorInterface::slotActivated);
    MessageComposer::ActionType type(action, MessageComposer::ActionType::Tools);
    setActionType(type);
}

void Rot13PluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void Rot13PluginEditorInterface::exec()
{
    const QString text = richTextEditor()->toPlainText();
    if (!text.isEmpty()) {
        Rot13Job job;
        job.setText(text);
        const QString convertedText = job.rot13();
        richTextEditor()->setPlainText(convertedText);
    }
}
