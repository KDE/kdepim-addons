/*
   Copyright (C) 2018 Montel Laurent <montel@kde.org>

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

#include "markdowninterface.h"
#include "markdownpreviewdialog.h"
#include "markdownplugin_debug.h"
#include <KLocalizedString>
#include <QAction>
#include <KActionCollection>
#include <KSharedConfig>
#include <KConfigGroup>
#include <KMessageBox>

MarkdownInterface::MarkdownInterface(QObject *parent)
    : MessageComposer::PluginEditorConvertTextInterface(parent)
{
}

MarkdownInterface::~MarkdownInterface()
{
}

void MarkdownInterface::createAction(KActionCollection *ac)
{
    mAction = new QAction(i18n("Generate HTML from markdown."), this);
    mAction->setCheckable(true);
    mAction->setChecked(false);
    ac->addAction(QStringLiteral("generate_markdown"), mAction);
    connect(mAction, &QAction::triggered, this, &MarkdownInterface::slotActivated);
    MessageComposer::PluginActionType type(mAction, MessageComposer::PluginActionType::Edit);
    setActionType(type);
}

bool MarkdownInterface::reformatText()
{
    return false;
}

bool MarkdownInterface::convertTextToFormat(MessageComposer::TextPart *textPart)
{
    if (mAction->isChecked()) {
        //Add messagebox
    } else {

    }
    return true;
}

void MarkdownInterface::reloadConfig()
{
//    KConfigGroup grp(KSharedConfig::openConfig(), "Mardown");
//    const QString cssname = grp.readEntry(QStringLiteral("cssname"), QString());

    //TODO load css !
}

void MarkdownInterface::slotActivated()
{
    qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "MarkdownInterface::slotActivated: not implemented yet!";
    //TODO signal/slot
}
