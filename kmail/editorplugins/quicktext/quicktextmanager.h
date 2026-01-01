/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

#include <memory>

class QAbstractItemModel;
class QItemSelectionModel;
class QuicktextManagerPrivate;
namespace MailCommon
{
class SnippetsModel;
}
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
    ~QuicktextManager() override;
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
    [[nodiscard]] bool snippetGroupSelected() const;

    /**
     * Returns the name of the currently selected snippet or snippet group.
     */
    [[nodiscard]] QString selectedName() const;

    void save();

    [[nodiscard]] QModelIndex currentGroupIndex() const;

    void importQuickText();
    void exportQuickText();

Q_SIGNALS:
    void insertPlainText(const QString &snippetText);

private:
    MailCommon::SnippetsModel *mModel = nullptr;
    QItemSelectionModel *mSelectionModel = nullptr;
    QWidget *const mParent;
};
