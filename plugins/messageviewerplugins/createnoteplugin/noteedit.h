/*
  SPDX-FileCopyrightText: 2014 Sandro Knauß <knauss@kolabsys.com>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef NOTEEDIT_H
#define NOTEEDIT_H

#include <QWidget>

#include <AkonadiCore/Collection>
#include <Akonadi/Notes/NoteUtils>
#include <KMime/KMimeMessage>

class QLineEdit;
class QPushButton;
namespace Akonadi {
class CollectionComboBox;
}

namespace MessageViewer {
class NoteEdit : public QWidget
{
    Q_OBJECT
public:
    explicit NoteEdit(QWidget *parent = nullptr);
    ~NoteEdit() override;

    Akonadi::Collection collection() const;
    void setCollection(const Akonadi::Collection &value);

    KMime::Message::Ptr message() const;
    void setMessage(const KMime::Message::Ptr &value);

    void writeConfig();
    void showNoteEdit();

public Q_SLOTS:
    void slotCloseWidget();

Q_SIGNALS:
    void createNote(const KMime::Message::Ptr &note, const Akonadi::Collection &collection);
    void collectionChanged(const Akonadi::Collection &col);
    void messageChanged(const KMime::Message::Ptr &msg);

protected:
    bool eventFilter(QObject *object, QEvent *e) override;
private:
    void slotReturnPressed();
    void slotCollectionChanged(int);
    void slotUpdateButtons(const QString &subject);
    void readConfig();
    Akonadi::Collection mCollection;
    KMime::Message::Ptr mMessage;
    QLineEdit *mNoteEdit = nullptr;
    Akonadi::CollectionComboBox *mCollectionCombobox = nullptr;
    QPushButton *mSaveButton = nullptr;
};
}

#endif // NOTEEDIT_H
