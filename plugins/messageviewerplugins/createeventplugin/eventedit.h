/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

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

    [[nodiscard]] Akonadi::Collection collection() const;
    void setCollection(const Akonadi::Collection &value);

    [[nodiscard]] std::shared_ptr<KMime::Message> message() const;
    void setMessage(const std::shared_ptr<KMime::Message> &value);

    void writeConfig();
    void showEventEdit();

public Q_SLOTS:
    void slotCloseWidget();

Q_SIGNALS:
    void createEvent(const KCalendarCore::Event::Ptr &event, const Akonadi::Collection &collection);
    void collectionChanged(const Akonadi::Collection &col);
    void messageChanged(const std::shared_ptr<KMime::Message> &msg);

protected:
    bool eventFilter(QObject *object, QEvent *e) override;

private:
    void slotReturnPressed();
    void slotCollectionChanged(int);
    void slotOpenEditor();
    void slotStartDateTimeChanged(const QDateTime &newDateTime);
    void slotUpdateButtons(const QString &subject);

    void slotEndDateTimeChanged(const QDateTime &newDateTime);
    [[nodiscard]] KCalendarCore::Event::Ptr createEventItem();
    void readConfig();
    void comboboxRowInserted();
    Akonadi::Collection mCollection;
    std::shared_ptr<KMime::Message> mMessage;
    QLineEdit *const mEventEdit;
    Akonadi::CollectionComboBox *mCollectionCombobox = nullptr;
    EventDateTimeWidget *const mStartDateTimeEdit;
    EventDateTimeWidget *const mEndDateTimeEdit;
    QPushButton *const mSaveButton;
    QPushButton *const mOpenEditorButton;
};
}
