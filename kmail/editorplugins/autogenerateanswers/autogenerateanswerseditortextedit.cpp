/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateanswerseditortextedit.h"
#include <KLocalizedString>
#include <QContextMenuEvent>
#include <QMenu>

AutoGenerateAnswersEditorTextEdit::AutoGenerateAnswersEditorTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
}

AutoGenerateAnswersEditorTextEdit::~AutoGenerateAnswersEditorTextEdit() = default;

void AutoGenerateAnswersEditorTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *popup = createStandardContextMenu();
    if (popup) {
        popup->addSeparator();
        auto action = new QAction(i18nc("@action", "Insert Text"), this);
        popup->addAction(action);
        connect(action, &QAction::triggered, this, [this]() {
            Q_EMIT insertText(toPlainText());
        });

        popup->exec(event->globalPos());
        delete popup;
    }
}
