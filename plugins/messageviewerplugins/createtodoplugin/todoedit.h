/*
   Copyright (C) 2014-2017 Montel Laurent <montel@kde.org>

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

#ifndef TODOEDIT_H
#define TODOEDIT_H

#include <QWidget>
#include <AkonadiCore/Collection>
#include <KMime/Message>
#include <KCalCore/Todo>

class KMessageWidget;
class QLineEdit;
class QPushButton;
namespace Akonadi {
class CollectionComboBox;
}

namespace MessageViewer {
class TodoEdit : public QWidget
{
    Q_OBJECT
public:
    explicit TodoEdit(QWidget *parent = nullptr);
    ~TodoEdit();

    Akonadi::Collection collection() const;
    void setCollection(const Akonadi::Collection &value);

    KMime::Message::Ptr message() const;
    void setMessage(const KMime::Message::Ptr &value);

    void writeConfig();

    void showToDoWidget();
    void setCurrentCollection(const Akonadi::Collection &col);
public Q_SLOTS:
    void slotCloseWidget();

Q_SIGNALS:
    void createTodo(const KCalCore::Todo::Ptr &todo, const Akonadi::Collection &collection);
    void collectionChanged(const Akonadi::Collection &col);
    void messageChanged(const KMime::Message::Ptr &msg);

protected:
    bool eventFilter(QObject *object, QEvent *e) override;
private:
    KCalCore::Todo::Ptr createTodoItem();
    void comboboxRowInserted();
    void slotReturnPressed();
    void slotCollectionChanged(int);
    void slotOpenEditor();
    void slotTextEdited(const QString &subject);
    void updateButtons(const QString &subject);
    void readConfig();
    Akonadi::Collection mCollection;
    Akonadi::Collection mCurrentCollection;
    KMime::Message::Ptr mMessage;
    QLineEdit *mNoteEdit;
    Akonadi::CollectionComboBox *mCollectionCombobox;
    KMessageWidget *mMsgWidget;
    QPushButton *mSaveButton;
    QPushButton *mOpenEditorButton;
};
}
#endif // TODOEDIT_H
