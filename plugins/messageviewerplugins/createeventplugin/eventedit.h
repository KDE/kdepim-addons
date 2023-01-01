/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

#include <Akonadi/Collection>
#include <KCalendarCore/Event>
#include <KMime/Message>

class QLineEdit;
class QPushButton;
namespace Akonadi
{
class CollectionComboBox;
}

namespace MessageViewer
{
class EventDateTimeWidget;
class EventEdit : public QWidget
{
    Q_OBJECT
public:
    explicit EventEdit(QWidget *parent = nullptr);
    ~EventEdit() override;

    Q_REQUIRED_RESULT Akonadi::Collection collection() const;
    void setCollection(const Akonadi::Collection &value);

    Q_REQUIRED_RESULT KMime::Message::Ptr message() const;
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
    QLineEdit *const mEventEdit;
    Akonadi::CollectionComboBox *mCollectionCombobox = nullptr;
    EventDateTimeWidget *const mStartDateTimeEdit;
    EventDateTimeWidget *const mEndDateTimeEdit;
    QPushButton *const mSaveButton;
    QPushButton *const mOpenEditorButton;
};
}
