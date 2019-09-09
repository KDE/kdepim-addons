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
#include <KStandardAction>
#include <QDesktopServices>

#include <QMenu>
#include <QAction>
#include <QTextBlock>
#include <QTextDocument>
#include <QPainter>
#include <KColorScheme>

GrammarResultTextEdit::GrammarResultTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    setReadOnly(true);
    setAcceptRichText(false);
    generalPaletteChanged();
}

GrammarResultTextEdit::~GrammarResultTextEdit()
{
}

void GrammarResultTextEdit::paintEvent(QPaintEvent *event)
{
    if (document()->isEmpty()) {
        const QString label = i18n("Any text to check.");

        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        if (!mTextColor.isValid()) {
            generalPaletteChanged();
        }
        p.setPen(mTextColor);

        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, label);
    } else {
        QTextEdit::paintEvent(event);
    }
}

void GrammarResultTextEdit::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
    const KStatefulBrush bgBrush = KStatefulBrush(KColorScheme::View, KColorScheme::NegativeText);
    mNegativeTextColor = bgBrush.brush(this).color();
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
            format.setBackground(info.color().isValid() ? info.color() : mNegativeTextColor);
            QString toolTip = info.error();
            //TODO generate new tooltip!
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
                if (!act.infoUrls().isEmpty()) {
                    QMenu *popupUrlInfo = popup->addMenu(i18n("Online Grammar Information"));
                    for (const QString &str : act.infoUrls()) {
                        QAction *actUrlInfo = popupUrlInfo->addAction(str);
                        connect(actUrlInfo, &QAction::triggered, this, [this, str]() {
                            slotOpenGrammarUrlInfo(str);
                        });
                    }
                }
            } else {
                qCDebug(LIBGRAMMARCOMMON_LOG) << " no suggestion " << act;
            }
        }
        popup->addSeparator();
        QAction *checkAgainAct = popup->addAction(QIcon::fromTheme(QStringLiteral("view-refresh")), i18n("Check Again"));
        connect(checkAgainAct, &QAction::triggered, this, &GrammarResultTextEdit::checkAgain);
        popup->addSeparator();
        QAction *closeAct = KStandardAction::close(this, &GrammarResultTextEdit::closeChecker, this);
        closeAct->setShortcut({});
        popup->addAction(closeAct);
        popup->exec(event->globalPos());
        delete popup;
    }
}

void GrammarResultTextEdit::slotOpenGrammarUrlInfo(const QString &url)
{
    QDesktopServices::openUrl(QUrl(url));
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
        const int diff = act.length() - replacementWord.length();
        if (diff != 0) {
            const int blockLength = block.length();
            for (int i = position + replacementWord.length() + 1; i < blockLength; ++i) {
                cur.setPosition(i);
                QTextCharFormat currentCharFormat = cur.charFormat();
                if (currentCharFormat.hasProperty(ReplaceFormatInfo)) {
                    MessageComposer::PluginGrammarAction act = cur.charFormat().property(ReplaceFormatInfo).value<MessageComposer::PluginGrammarAction>();
                    act.setStart(act.start() - diff);
                    currentCharFormat.setProperty(ReplaceFormatInfo, QVariant::fromValue(act));

                    const int newPosition = i - 1;
                    cur.setPosition(newPosition);
                    cur.setPosition(newPosition + act.length(), QTextCursor::KeepAnchor);
                    cur.setCharFormat(currentCharFormat);

                    i += act.length();
                }
            }
        }
    }

    Q_EMIT replaceText(actWithReplacement);
}
