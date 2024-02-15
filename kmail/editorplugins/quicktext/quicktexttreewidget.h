/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "quicktext_export.h"
#include <QTreeView>
class QContextMenuEvent;

class QuicktextManager;
class QUICKTEXT_EXPORT QuicktextTreeWidget : public QTreeView
{
    Q_OBJECT
public:
    explicit QuicktextTreeWidget(QuicktextManager *manager, QWidget *parent = nullptr);
    ~QuicktextTreeWidget() override;

    [[nodiscard]] QuicktextManager *snippetsManager() const;

protected:
    void contextMenuEvent(QContextMenuEvent *) override;
    void dropEvent(QDropEvent *) override;

Q_SIGNALS:
    void insertSnippetText(const QString &str);

    void addSnippet();
    void editSnippet();
    void addSnippetGroup();
    void editSnippetGroup();

private:
    QUICKTEXT_NO_EXPORT void deleteSnippet();
    QUICKTEXT_NO_EXPORT void deleteSnippetGroup();
    QUICKTEXT_NO_EXPORT void selectionWasChanged();
    QuicktextManager *const mSnippetsManager;
    QAction *mAddSnippetAction = nullptr;
    QAction *mEditSnippetAction = nullptr;
    QAction *mDeleteSnippetAction = nullptr;
    QAction *mAddSnippetGroupAction = nullptr;
    QAction *mEditSnippetGroupAction = nullptr;
    QAction *mDeleteSnippetGroupAction = nullptr;
};
