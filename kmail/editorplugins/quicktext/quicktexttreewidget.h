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
#ifndef QUICKTEXT_QUICKTEXTTREEWIDGET_H
#define QUICKTEXT_QUICKTEXTTREEWIDGET_H

#include <QTreeView>
#include "quicktext_export.h"
class QContextMenuEvent;

class QuicktextManager;
class QUICKTEXT_EXPORT QuicktextTreeWidget : public QTreeView
{
    Q_OBJECT
public:
    explicit QuicktextTreeWidget(QuicktextManager *manager, QWidget *parent = nullptr);
    ~QuicktextTreeWidget() override;

    QuicktextManager *snippetsManager() const;

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
    void deleteSnippet();
    void deleteSnippetGroup();
    void selectionWasChanged();
    QuicktextManager *mSnippetsManager = nullptr;
    QAction *mAddSnippetAction = nullptr;
    QAction *mEditSnippetAction = nullptr;
    QAction *mDeleteSnippetAction = nullptr;
    QAction *mAddSnippetGroupAction = nullptr;
    QAction *mEditSnippetGroupAction = nullptr;
    QAction *mDeleteSnippetGroupAction = nullptr;
};

#endif
