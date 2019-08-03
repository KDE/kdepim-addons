/*
   Copyright (C) 2014-2019 Montel Laurent <montel@kde.org>

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

#ifndef EVENTEDIT_H
#define EVENTEDIT_H

#include <QWidget>

#include <AkonadiCore/Collection>
#include <KMime/Message>
#include <KCalendarCore/Event>

class QLineEdit;
class QPushButton;
namespace Akonadi {
class CollectionComboBox;
}

namespace MessageViewer {
class EventDateTimeWidget;
class EventEdit : public QWidget
{
    Q_OBJECT
public:
    explicit EventEdit(QWidget *parent = nullptr);
    ~EventEdit() override;

    Akonadi::Collection collection() const;
    void setCollection(const Akonadi::Collection &value);

    KMime::Message::Ptr message() const;
    void setMessage(const KMime::Message::Ptr &value);

    void writeConfig();
    void showEventEdit();

public Q_SLOTS:
    void slotCloseWidget();

private Q_SLOTS:
    void slotReturnPressed();
    void slotCollectionChanged(int);
    void slotOpenEditor();
    void slotStartDateTimeChanged(const QDateTime &newDateTime);
    void slotUpdateButtons(const QString &subject);

    void slotEndDateTimeChanged(const QDateTime &newDateTime);
Q_SIGNALS:
    void createEvent(const KCalendarCore::Event::Ptr &event, const Akonadi::Collection &collection);
    void collectionChanged(const Akonadi::Collection &col);
    void messageChanged(const KMime::Message::Ptr &msg);

protected:
    bool eventFilter(QObject *object, QEvent *e) override;
private:
    KCalendarCore::Event::Ptr createEventItem();
    void readConfig();
    void comboboxRowInserted();
    Akonadi::Collection mCollection;
    KMime::Message::Ptr mMessage;
    QLineEdit *mEventEdit = nullptr;
    Akonadi::CollectionComboBox *mCollectionCombobox = nullptr;
    EventDateTimeWidget *mStartDateTimeEdit = nullptr;
    EventDateTimeWidget *mEndDateTimeEdit = nullptr;
    QPushButton *mSaveButton = nullptr;
    QPushButton *mOpenEditorButton = nullptr;
};
}

#endif // EVENTEDIT_H
