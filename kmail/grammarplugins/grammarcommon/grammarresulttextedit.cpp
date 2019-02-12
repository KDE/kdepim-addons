/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#include "grammarresulttextedit.h"
#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>
#include "grammarcommon_debug.h"

#include <KLocalizedString>

#include <QMenu>
#include <QAction>
#include <QTextBlock>
#include <QTextDocument>

GrammarResultTextEdit::GrammarResultTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    setReadOnly(true);
    setAcceptRichText(false);
}

GrammarResultTextEdit::~GrammarResultTextEdit()
{
}

void GrammarResultTextEdit::applyGrammarResult(const QVector<GrammarError> &infos)
{
    for (const GrammarError &info : infos) {
        //Block id based on 1 not 0 as QTextDocument (perhaps remove -1 when loading ?)
        QTextBlock block = document()->findBlockByNumber(info.blockId() - 1);
        if (block.isValid()) {
            QTextCursor cur(block);
            QTextCharFormat format;
            //Verify color
            format.setBackground(info.color().isValid() ? info.color() : QColor(Qt::red));
            format.setToolTip(info.error());
            MessageComposer::PluginGrammarAction act;
            act.setLength(info.length());
            act.setStart(info.start());
            act.setSuggestions(info.suggestions());
            act.setBlockId(info.blockId());
            format.setProperty(ReplaceFormatInfo, QVariant::fromValue(act));
            const int position = cur.position() + info.start();
            cur.setPosition(position);
            cur.setPosition(position + info.length(), QTextCursor::KeepAnchor);
            cur.mergeCharFormat(format);
        } else {
            qCWarning(LIBGRAMMARCOMMON_LOG) << "Unable to find block Id" << (info.blockId() -1);
        }
    }
}

void GrammarResultTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *popup = createStandardContextMenu();
    if (popup) {
        QTextCursor cursor = cursorForPosition(event->pos());
        if (cursor.charFormat().hasProperty(ReplaceFormatInfo)) {
            const MessageComposer::PluginGrammarAction act = cursor.charFormat().property(ReplaceFormatInfo).value<MessageComposer::PluginGrammarAction>();
            const QStringList sugg = act.suggestions();
            if (!sugg.isEmpty()) {
                popup->addSeparator();
                QMenu *popupReplacement = popup->addMenu(i18n("Replacement"));
                for (const QString &str : act.suggestions()) {
                    QAction *actReplacement = popupReplacement->addAction(str);
                    connect(actReplacement, &QAction::triggered, this, [this, act, str]() {
                        slotReplaceWord(act, str);
                    });
                }
            } else {
                qCDebug(LIBGRAMMARCOMMON_LOG) << " no suggestion " << act;
            }
        }
        popup->addSeparator();
        QAction *checkAgainAct = popup->addAction(i18n("Check Again"));
        connect(checkAgainAct, &QAction::triggered, this, &GrammarResultTextEdit::checkAgain);
        popup->exec(event->globalPos());
        delete popup;
    }
}

void GrammarResultTextEdit::slotReplaceWord(const MessageComposer::PluginGrammarAction &act, const QString &replacementWord)
{
    MessageComposer::PluginGrammarAction actWithReplacement = act;
    actWithReplacement.setReplacement(replacementWord);

    QTextBlock block = document()->findBlockByNumber(act.blockId() - 1);
    if (block.isValid()) {
        QTextCursor cur(block);
        const int position = cur.position() + act.start();
        cur.setPosition(position);
        cur.setPosition(position + act.length(), QTextCursor::KeepAnchor);
        QTextCharFormat format;

        cur.insertText(replacementWord, format);
        if (act.length() != replacementWord.length()) {
            qDebug() << " We need to update act";
        }
    }

    Q_EMIT replaceText(actWithReplacement);
}
