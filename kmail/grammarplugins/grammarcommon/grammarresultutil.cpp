/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammarresultutil.h"
#include "grammarcommon_debug.h"

#include <KLocalizedString>
#include <QTextBlock>
#include <QTextDocument>

void GrammarResultUtil::applyGrammarResult(const QVector<GrammarError> &infos, QTextDocument *document, const QColor &negativeTextColor)
{
    for (const GrammarError &info : infos) {
        // Block id based on 1 not 0 as QTextDocument (perhaps remove -1 when loading ?)
        QTextBlock block = document->findBlockByNumber(info.blockId() - 1);
        if (block.isValid()) {
            QTextCursor cur(block);
            QTextCharFormat format;
            // Verify color
            format.setBackground(info.color().isValid() ? info.color() : negativeTextColor);
            QString toolTip = info.error();
            // TODO generate new tooltip!
            if (!info.url().isEmpty()) {
                toolTip += QLatin1Char('\n') + i18n("See on: %1", info.url());
            }
            format.setToolTip(toolTip);
            MessageComposer::PluginGrammarAction act;
            act.setLength(info.length());
            act.setStart(info.start());
            act.setSuggestions(info.suggestions());
            act.setBlockId(info.blockId());
            if (!info.url().isEmpty()) {
                act.setInfoUrls({info.url()});
            }
            format.setProperty(ReplaceFormatInfo, QVariant::fromValue(act));
            const int position = cur.position() + info.start();
            cur.setPosition(position);
            cur.setPosition(position + info.length(), QTextCursor::KeepAnchor);
            cur.mergeCharFormat(format);
        } else {
            qCWarning(LIBGRAMMARCOMMON_LOG) << "Unable to find block Id" << (info.blockId() - 1);
        }
    }
}

void GrammarResultUtil::replaceWord(const MessageComposer::PluginGrammarAction &act, const QString &replacementWord, QTextDocument *document)
{
    QTextBlock block = document->findBlockByNumber(act.blockId() - 1);
    if (block.isValid()) {
        QTextCursor cur(block);
        const int position = cur.position() + act.start();
        cur.setPosition(position);
        cur.setPosition(position + act.length(), QTextCursor::KeepAnchor);
        QTextCharFormat format;
        cur.insertText(replacementWord, format);
        const int diff = replacementWord.length() - act.length();
        // qDebug() << " diff " << diff;
        if (diff != 0) {
            const int blockLength = block.length();
            for (int i = position + replacementWord.length() + 1; i < blockLength; ++i) {
                cur.setPosition(i);
                // qDebug() << " XCWCWXCWCWXCWXCCX  " << i;
                QTextCharFormat currentCharFormat = cur.charFormat();
                if (currentCharFormat.hasProperty(GrammarResultUtil::TextInfo::ReplaceFormatInfo)) {
                    auto act = cur.charFormat().property(GrammarResultUtil::TextInfo::ReplaceFormatInfo).value<MessageComposer::PluginGrammarAction>();
                    // qDebug() << "BEFORE DDDDDDDDDDDDDDDD" << act.start();
                    act.setStart(act.start() + diff);
                    // qDebug() << "AFTER DDDDDDDDDDDDDDDD" << act.start();
                    currentCharFormat.setProperty(GrammarResultUtil::TextInfo::ReplaceFormatInfo, QVariant::fromValue(act));

                    const int newPosition = i - 1;
                    // qDebug() << " newPosition " << newPosition;
                    cur.setPosition(newPosition);
                    cur.setPosition(newPosition + act.length(), QTextCursor::KeepAnchor);
                    // qDebug() << "2222 newPosition " << newPosition + act.length();
                    cur.setCharFormat(currentCharFormat);

                    i += act.length();
                }
            }
            // qDebug() << " block.blockNumber() " << block.blockNumber() << " document->blockCount() " << document->blockCount();
            for (int b = block.blockNumber() + 1; b < document->blockCount(); ++b) {
                QTextBlock block = document->findBlockByNumber(b);
                if (block.isValid()) {
                    QTextCursor cur(block);
                    const int blockLength = block.length();
                    for (int i = 0; i < blockLength; ++i) {
                        cur.setPosition(block.length() + i);
                        QTextCharFormat currentCharFormat = cur.charFormat();
                        if (currentCharFormat.hasProperty(GrammarResultUtil::TextInfo::ReplaceFormatInfo)) {
                            auto act = cur.charFormat().property(GrammarResultUtil::TextInfo::ReplaceFormatInfo).value<MessageComposer::PluginGrammarAction>();
                            // qDebug() << "BEFORE DDDDDDDDDDDDDDDD" << act.start();
                            act.setStart(act.start() + diff);
                            // qDebug() << "AFTER DDDDDDDDDDDDDDDD" << act.start();
                            currentCharFormat.setProperty(GrammarResultUtil::TextInfo::ReplaceFormatInfo, QVariant::fromValue(act));

                            const int newPosition = act.start() - 1;
                            // qDebug() << " newPosition " << newPosition;
                            cur.setPosition(newPosition);
                            cur.setPosition(newPosition + act.length(), QTextCursor::KeepAnchor);
                            // qDebug() << "2222 newPosition " << newPosition + act.length();
                            cur.setCharFormat(currentCharFormat);

                            i += act.length();
                        }
                    }
                }
            }
        }
    }
}
