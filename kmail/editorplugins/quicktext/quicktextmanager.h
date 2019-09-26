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

#ifndef QUICKTEXT_MANAGER_H
#define QUICKTEXT_MANAGER_H

#include <QObject>

class KActionCollection;

class QAbstractItemModel;
class QAction;
class QItemSelectionModel;
class QuicktextManager : public QObject
{
    Q_OBJECT
public:
    /**
     * Creates a new snippets manager.
     *
     * @param parent The parent object.
     * @param widget The widget.
     */
    explicit QuicktextManager(QObject *parent = nullptr, QWidget *widget = nullptr);

    /**
     * Destroys the snippets manager.
     */
    ~QuicktextManager();
    /**
     * Returns the model that represents the snippets.
     */
    QAbstractItemModel *model() const;

    /**
     * Returns the selection model that is used by the manager to select the
     * snippet or snippet group to work on.
     */
    QItemSelectionModel *selectionModel() const;

    /**
     * Returns whether the currently selected item is a snippet group.
     */
    Q_REQUIRED_RESULT bool snippetGroupSelected() const;

    /**
     * Returns the name of the currently selected snippet or snippet group.
     */
    Q_REQUIRED_RESULT QString selectedName() const;

    void save();

    Q_REQUIRED_RESULT QModelIndex currentGroupIndex() const;
    void setDirty(bool b);
Q_SIGNALS:
    void insertSnippet();
    void insertPlainText(const QString &snippetText);

private:
    //@cond PRIVATE
    class Private;
    Private *const d;
    //@endcond
};

#endif
