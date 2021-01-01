/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "quicktextplugineditorinterface.h"
#include "quicktextmenu.h"
#include <KPIMTextEdit/RichTextEditor>
#include <MessageComposer/PluginComposerInterface>
#include <MessageComposer/ConvertSnippetVariablesJob>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <QPushButton>
#include <QTextBlock>
#include <QDebug>

QuickTextPluginEditorInterface::QuickTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
    , mModel(MailCommon::SnippetsModel::instance())
{
    updateSnippetsInfo();
}

QuickTextPluginEditorInterface::~QuickTextPluginEditorInterface()
{
}

void QuickTextPluginEditorInterface::updateSnippetsInfo()
{
    mSnippetsInfo = mModel->snippetsInfo();
}

void QuickTextPluginEditorInterface::createAction(KActionCollection *ac)
{
    auto *quickTextMenu = new QuickTextMenu(parentWidget(), this);
    quickTextMenu->setPluginComposerInterface(composerInterface());
    connect(quickTextMenu, &QuickTextMenu::insertText, this, &QuickTextPluginEditorInterface::insertText);
    QAction *action = new QAction(i18n("Variables"), this);
    action->setMenu(quickTextMenu->menu());
    ac->addAction(QStringLiteral("insert_variables"), action);
    connect(action, &QAction::triggered, this, &QuickTextPluginEditorInterface::slotActivated);
    MessageComposer::PluginActionType type(action, MessageComposer::PluginActionType::Edit);
    setActionType(type);
    QPushButton *button = new QPushButton(i18n("Variables"));
    button->setFocusPolicy(Qt::NoFocus);
    button->setMenu(quickTextMenu->menu());
    setStatusBarWidget(button);
}

void QuickTextPluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void QuickTextPluginEditorInterface::exec()
{
}

void QuickTextPluginEditorInterface::reloadConfig()
{
    updateSnippetsInfo();
}

bool QuickTextPluginEditorInterface::processProcessKeyEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Tab) {
        if (!richTextEditor()->textCursor().hasSelection()) {
            //const QTextCharFormat initialTextFormat = richTextEditor()->textCursor().charFormat();
            const int position = richTextEditor()->textCursor().position();
            QTextCursor cur = richTextEditor()->textCursor();
            selectPreviousWord(cur, position);
            const QString selectedWord = cur.selectedText();
            if (selectedWord.isEmpty()) {
                return false;
            }
            //qDebug() << "selected " << selectedWord;
            for (const MailCommon::SnippetsInfo &info : qAsConst(mSnippetsInfo)) {
                //qDebug() << " info.keyword" << info.keyword;
                QString infoKeyword = info.keyword;
                if (!infoKeyword.startsWith(QLatin1Char('\\'))) {
                    infoKeyword = QLatin1Char('\\') + infoKeyword;
                }
                if (infoKeyword == selectedWord) {
                    qDebug() << "found snippetsinfo " << info.keyword;
                    cur.insertText(composerInterface()->convertText(info.text));
                    //TODO change pos cur.setPosition(position);
                    return true;
                }
            }
        }
    }

    return false;
}

void QuickTextPluginEditorInterface::selectPreviousWord(QTextCursor &cursor, int cursorPosition)
{
    cursor.setPosition(cursorPosition);
    QTextBlock block = cursor.block();
    cursor.setPosition(block.position());
    cursorPosition -= block.position();
    QString string = block.text();
    int pos = 0;
    bool space = false;
    QString::Iterator iter = string.begin();
    while (iter != string.end()) {
        if (iter->isSpace()) {
            if (space) {
                // double spaces belong to the previous word
            } else if (pos < cursorPosition) {
                cursor.setPosition(pos + block.position() + 1);    // +1 because we don't want to set it on the space itself
            } else {
                space = true;
            }
        } else if (space) {
            break;
        }
        ++pos;
        ++iter;
    }
    cursor.setPosition(pos + block.position(), QTextCursor::KeepAnchor);
}
