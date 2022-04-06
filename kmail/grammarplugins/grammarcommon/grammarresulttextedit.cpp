/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammarresulttextedit.h"
#include "grammarcommon_debug.h"
#include <MessageComposer/PluginEditorGrammarCustomToolsViewInterface>

#include <KLocalizedString>
#include <KStandardAction>
#include <QDesktopServices>

#include <KColorScheme>
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QPainter>
#include <QTextBlock>
#include <QTextDocument>

GrammarResultTextEdit::GrammarResultTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    setReadOnly(true);
    setAcceptRichText(false);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    connect(qApp, &QApplication::paletteChanged, this, &GrammarResultTextEdit::generalPaletteChanged);
#endif
    generalPaletteChanged();
}

GrammarResultTextEdit::~GrammarResultTextEdit() = default;

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

bool GrammarResultTextEdit::event(QEvent *ev)
{
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    if (ev->type() == QEvent::ApplicationPaletteChange) {
        regenerateColorScheme();
    }
#endif
    return QTextEdit::event(ev);
}

void GrammarResultTextEdit::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
    const KStatefulBrush bgBrush = KStatefulBrush(KColorScheme::View, KColorScheme::NegativeText);
    mNegativeTextColor = bgBrush.brush(palette).color();
}

void GrammarResultTextEdit::applyGrammarResult(const QVector<GrammarError> &infos)
{
    for (const GrammarError &info : infos) {
        // Block id based on 1 not 0 as QTextDocument (perhaps remove -1 when loading ?)
        QTextBlock block = document()->findBlockByNumber(info.blockId() - 1);
        if (block.isValid()) {
            QTextCursor cur(block);
            QTextCharFormat format;
            // Verify color
            format.setBackground(info.color().isValid() ? info.color() : mNegativeTextColor);
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

void GrammarResultTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *popup = createStandardContextMenu();
    if (popup) {
        QTextCursor cursor = cursorForPosition(event->pos());
        if (cursor.charFormat().hasProperty(ReplaceFormatInfo)) {
            const auto act = cursor.charFormat().property(ReplaceFormatInfo).value<MessageComposer::PluginGrammarAction>();
            const QStringList sugg = act.suggestions();
            if (!sugg.isEmpty()) {
                popup->addSeparator();
                QMenu *popupReplacement = popup->addMenu(i18n("Replacement"));
                for (const QString &str : sugg) {
                    QAction *actReplacement = popupReplacement->addAction(str);
                    connect(actReplacement, &QAction::triggered, this, [this, act, str]() {
                        slotReplaceWord(act, str);
                    });
                }
                const QStringList lst = act.infoUrls();
                if (!lst.isEmpty()) {
                    QMenu *popupUrlInfo = popup->addMenu(i18n("Online Grammar Information"));
                    for (const QString &str : lst) {
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
        QAction *configureAct = popup->addAction(QIcon::fromTheme(QStringLiteral("settings-configure")), i18n("Configure..."));
        connect(configureAct, &QAction::triggered, this, &GrammarResultTextEdit::configure);
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
                    auto act = cur.charFormat().property(ReplaceFormatInfo).value<MessageComposer::PluginGrammarAction>();
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
