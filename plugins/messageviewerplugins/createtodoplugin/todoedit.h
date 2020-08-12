/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TODOEDIT_H
#define TODOEDIT_H

#include <QWidget>
#include <AkonadiCore/Collection>
#include <KMime/Message>
#include <KCalendarCore/Todo>

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
    ~TodoEdit() override;

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
    void createTodo(const KCalendarCore::Todo::Ptr &todo, const Akonadi::Collection &collection);
    void collectionChanged(const Akonadi::Collection &col);
    void messageChanged(const KMime::Message::Ptr &msg);

protected:
    bool eventFilter(QObject *object, QEvent *e) override;
private:
    KCalendarCore::Todo::Ptr createTodoItem();
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
    QLineEdit *mNoteEdit = nullptr;
    Akonadi::CollectionComboBox *mCollectionCombobox = nullptr;
    KMessageWidget *mMsgWidget = nullptr;
    QPushButton *mSaveButton = nullptr;
    QPushButton *mOpenEditorButton = nullptr;
};
}
#endif // TODOEDIT_H
