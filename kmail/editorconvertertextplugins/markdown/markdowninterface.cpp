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
#include "markdownconverter.h"
#include <KPIMTextEdit/RichTextComposer>
#include <KPIMTextEdit/RichTextComposerControler>
#include <KLocalizedString>
#include <QAction>
#include <KActionCollection>
#include <KSharedConfig>
#include <KConfigGroup>
#include <KMessageBox>
#include <QPointer>
#include <MessageComposer/TextPart>

MarkdownInterface::MarkdownInterface(QObject *parent)
    : MessageComposer::PluginEditorConvertTextInterface(parent)
{
}

MarkdownInterface::~MarkdownInterface()
{
}

void MarkdownInterface::createAction(KActionCollection *ac)
{
    mAction = new QAction(i18n("Generate HTML from markdown language."), this);
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

MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus MarkdownInterface::convertTextToFormat(MessageComposer::TextPart *textPart)
{
    if (mAction->isChecked()) {
        const QString str = richTextEditor()->composerControler()->toCleanPlainText();
        if (!str.isEmpty()) {
            if (KMessageBox::Yes == KMessageBox::warningYesNo(parentWidget(), i18n("Do you still want to convert text to HTML?"), i18n("Convert Markdown Language"))) {
                MarkdownConverter converter;
                converter.setEnableEmbeddedLabel(mEnableEmbeddedLabel);
                converter.setEnableExtraDefinitionLists(mEnableExtraDefinitionLists);
                const QString result = converter.convertTextToMarkdown(str);
                if (!result.isEmpty()) {
                    textPart->setCleanPlainText(str);
                    textPart->setWrappedPlainText(richTextEditor()->composerControler()->toWrappedPlainText());
                    textPart->setCleanHtml(result);
                    return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::Converted;
                } else {
                    qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "Impossible to convert text";
                    return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::Error;
                }
            }
        } else {
            qCWarning(KMAIL_EDITOR_MARKDOWN_PLUGIN_LOG) << "empty text! Bug ?";
            return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::NotConverted;
        }
    }
    return MessageComposer::PluginEditorConvertTextInterface::ConvertTextStatus::NotConverted;
}

void MarkdownInterface::reloadConfig()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Mardown");

    mEnableEmbeddedLabel = grp.readEntry("Enable Embedded Latex", false);
    mEnableExtraDefinitionLists = grp.readEntry("Enable Extra Definition Lists", false);
}

void MarkdownInterface::slotActivated()
{
    if (mDialog.isNull()) {
        mDialog = new MarkdownPreviewDialog(parentWidget());
        mDialog->setText(richTextEditor()->toPlainText());
        connect(richTextEditor(), &KPIMTextEdit::RichTextEditor::textChanged, this, [this]()
        {
            mDialog->setText(richTextEditor()->toPlainText());
        }
        );
    }
    mDialog->show();
}
