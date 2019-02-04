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
#include "grammalecteplugin_debug.h"

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

void GrammarResultTextEdit::applyGrammarResult(const QVector<GrammalecteGrammarError> &infos)
{
    for (const GrammalecteGrammarError &info : infos) {
        //Block id based on 1 not 0 as QTextDocument (perhaps remove -1 when loading ?)
        QTextBlock block = document()->findBlockByNumber(info.blockId() - 1);
        if (block.isValid()) {
            QTextCursor cur(block);
            const int position = cur.position();
            QTextCharFormat format;
            //Verify color
            format.setBackground(info.color().isValid() ? info.color() : QColor(Qt::red));
            format.setToolTip(info.error());
            cur.setPosition(position + info.begin());
            cur.setPosition(position + info.end(), QTextCursor::KeepAnchor);
            cur.mergeCharFormat(format);
        } else {
            qCWarning(KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG) << "Unable to find block Id" << (info.blockId() -1);
        }
    }
}
