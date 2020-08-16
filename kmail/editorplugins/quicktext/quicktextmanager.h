/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef QUICKTEXT_MANAGER_H
#define QUICKTEXT_MANAGER_H

#include <QObject>


class QAbstractItemModel;
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

    void importQuickText();
    void exportQuickText();

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
