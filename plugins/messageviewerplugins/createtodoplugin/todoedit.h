/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Collection>
#include <KCalendarCore/Todo>
#include <KMime/Message>
#include <QWidget>

class KMessageWidget;
class QLineEdit;
class QPushButton;
namespace Akonadi
{
class CollectionComboBox;
}

namespace MessageViewer
{
class TodoEdit : public QWidget
{
    Q_OBJECT
public:
    explicit TodoEdit(QWidget *parent = nullptr);
    ~TodoEdit() override;

    [[nodiscard]] Akonadi::Collection collection() const;
    void setCollection(const Akonadi::Collection &value);

    [[nodiscard]] std::shared_ptr<KMime::Message> message() const;
    void setMessage(const std::shared_ptr<KMime::Message> &value);

    void writeConfig();

    void showToDoWidget();
    void setCurrentCollection(const Akonadi::Collection &col);
public Q_SLOTS:
    void slotCloseWidget();

Q_SIGNALS:
    void createTodo(const KCalendarCore::Todo::Ptr &todo, const Akonadi::Collection &collection);
    void collectionChanged(const Akonadi::Collection &col);
    void messageChanged(const std::shared_ptr<KMime::Message> &msg);

protected:
    bool eventFilter(QObject *object, QEvent *e) override;

private:
    [[nodiscard]] KCalendarCore::Todo::Ptr createTodoItem();
    void comboboxRowInserted();
    void slotReturnPressed();
    void slotCollectionChanged(int);
    void slotOpenEditor();
    void slotTextEdited(const QString &subject);
    void updateButtons(const QString &subject);
    void readConfig();
    Akonadi::Collection mCollection;
    Akonadi::Collection mCurrentCollection;
    std::shared_ptr<KMime::Message> mMessage;
    QLineEdit *mNoteEdit = nullptr;
    Akonadi::CollectionComboBox *mCollectionCombobox = nullptr;
    KMessageWidget *const mMsgWidget;
    QPushButton *const mSaveButton;
    QPushButton *const mOpenEditorButton;
};
}
