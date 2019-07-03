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

#include "eventedit.h"
#include "createeventplugin_debug.h"
#include "globalsettings_messageviewer.h"
#include "eventdatetimewidget.h"

#include <KLocalizedString>
#include <QLineEdit>
#include <QIcon>
#include <QDateTime>

#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QLabel>

#include <AkonadiWidgets/CollectionComboBox>
#include <QPushButton>

#include <IncidenceEditor/IncidenceDialogFactory>
#include <IncidenceEditor/IncidenceDialog>
#include <KGuiItem>
#include <KStandardGuiItem>

namespace MessageViewer {
QAbstractItemModel *_k_eventEditStubModel = nullptr;
}

using namespace MessageViewer;

EventEdit::EventEdit(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(5, 5, 5, 5);
    vbox->setSpacing(2);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setContentsMargins(0, 0, 0, 0);
    hbox->setSpacing(2);
    vbox->addLayout(hbox);

    QLabel *lab = new QLabel(i18n("Event:"), this);
    hbox->addWidget(lab);

    mEventEdit = new QLineEdit(this);
    mEventEdit->setClearButtonEnabled(true);
    mEventEdit->setObjectName(QStringLiteral("eventedit"));
    mEventEdit->setFocus();
    connect(mEventEdit, &QLineEdit::returnPressed, this, &EventEdit::slotReturnPressed);
    connect(mEventEdit, &QLineEdit::textChanged, this, &EventEdit::slotUpdateButtons);
    hbox->addWidget(mEventEdit);

    hbox->addSpacing(5);

    mCollectionCombobox = new Akonadi::CollectionComboBox(_k_eventEditStubModel, this);
    mCollectionCombobox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
    mCollectionCombobox->setMinimumWidth(250);
    mCollectionCombobox->setMimeTypeFilter(QStringList() << KCalCore::Event::eventMimeType());
    mCollectionCombobox->setObjectName(QStringLiteral("akonadicombobox"));
#ifndef QT_NO_ACCESSIBILITY
    mCollectionCombobox->setAccessibleDescription(i18n("Calendar where the new event will be stored."));
#endif
    mCollectionCombobox->setToolTip(i18n("Calendar where the new event will be stored"));

    connect(mCollectionCombobox, qOverload<int>(&Akonadi::CollectionComboBox::currentIndexChanged), this, &EventEdit::slotCollectionChanged);
    connect(mCollectionCombobox, qOverload<int>(&Akonadi::CollectionComboBox::activated), this, &EventEdit::slotCollectionChanged);
    connect(mCollectionCombobox->model(), &QAbstractItemModel::rowsInserted, this, &EventEdit::comboboxRowInserted);
    hbox->addWidget(mCollectionCombobox);

    hbox = new QHBoxLayout;
    hbox->setContentsMargins(0, 0, 0, 0);
    hbox->setSpacing(2);
    vbox->addLayout(hbox);

    lab = new QLabel(i18n("Start:"), this);
    hbox->addWidget(lab);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    mStartDateTimeEdit = new EventDateTimeWidget(this);
    mStartDateTimeEdit->setObjectName(QStringLiteral("startdatetimeedit"));
    mStartDateTimeEdit->setDateTime(currentDateTime);
#ifndef QT_NO_ACCESSIBILITY
    mStartDateTimeEdit->setAccessibleDescription(i18n("Select start time for event."));
#endif
    connect(mStartDateTimeEdit, &EventDateTimeWidget::dateTimeChanged, this, &EventEdit::slotStartDateTimeChanged);
    hbox->addWidget(mStartDateTimeEdit);

    hbox->addSpacing(5);

    lab = new QLabel(i18n("End:"), this);
    hbox->addWidget(lab);
    mEndDateTimeEdit = new EventDateTimeWidget(this);
    mEndDateTimeEdit->setObjectName(QStringLiteral("enddatetimeedit"));
    mEndDateTimeEdit->setDateTime(currentDateTime.addSecs(3600));
#ifndef QT_NO_ACCESSIBILITY
    mEndDateTimeEdit->setAccessibleDescription(i18n("Select end time for event."));
#endif
    connect(mEndDateTimeEdit, &EventDateTimeWidget::dateTimeChanged,
            this, &EventEdit::slotEndDateTimeChanged);

    hbox->addWidget(mEndDateTimeEdit);

    hbox->addStretch(1);

    hbox = new QHBoxLayout;
    hbox->setSpacing(2);
    hbox->setContentsMargins(0, 0, 0, 0);
    vbox->addLayout(hbox);

    hbox->addStretch(1);

    mSaveButton = new QPushButton(QIcon::fromTheme(QStringLiteral("appointment-new")), i18n("&Save"), this);
    mSaveButton->setObjectName(QStringLiteral("save-button"));
    mSaveButton->setEnabled(false);
#ifndef QT_NO_ACCESSIBILITY
    mSaveButton->setAccessibleDescription(i18n("Create new event and close this widget."));
#endif
    connect(mSaveButton, &QPushButton::clicked, this, &EventEdit::slotReturnPressed);
    hbox->addWidget(mSaveButton);

    mOpenEditorButton = new QPushButton(i18n("Open &editor..."), this);
#ifndef QT_NO_ACCESSIBILITY
    mOpenEditorButton->setAccessibleDescription(i18n("Open event editor, where more details can be changed."));
#endif
    mOpenEditorButton->setObjectName(QStringLiteral("open-editor-button"));
    mOpenEditorButton->setEnabled(false);
    connect(mOpenEditorButton, &QPushButton::clicked, this, &EventEdit::slotOpenEditor);
    hbox->addWidget(mOpenEditorButton);

    QPushButton *btn = new QPushButton(this);
    KGuiItem::assign(btn, KStandardGuiItem::cancel());
    btn->setObjectName(QStringLiteral("close-button"));
#ifndef QT_NO_ACCESSIBILITY
    btn->setAccessibleDescription(i18n("Close the widget for creating new events."));
#endif
    connect(btn, &QPushButton::clicked, this, &EventEdit::slotCloseWidget);
    hbox->addWidget(btn);

    readConfig();
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    installEventFilter(this);
    mCollectionCombobox->installEventFilter(this);
}

EventEdit::~EventEdit()
{
    writeConfig();
}

void EventEdit::comboboxRowInserted()
{
    slotUpdateButtons(mEventEdit->text());
}

void EventEdit::writeConfig()
{
    const Akonadi::Collection col = mCollectionCombobox->currentCollection();
    // col might not be valid if the collection wasn't found yet (the combo is async), skip saving in that case.
    if (col.isValid() && col.id() != MessageViewer::MessageViewerSettingsBase::self()->lastEventSelectedFolder()) {
        MessageViewer::MessageViewerSettingsBase::self()->setLastEventSelectedFolder(col.id());
        MessageViewer::MessageViewerSettingsBase::self()->save();
    }
}

void EventEdit::slotUpdateButtons(const QString &subject)
{
    const bool subjectIsNotEmpty = !subject.trimmed().isEmpty();
    const bool collectionComboboxEmpty = (mCollectionCombobox->count() < 1);
    mSaveButton->setEnabled(subjectIsNotEmpty && !collectionComboboxEmpty);
    mOpenEditorButton->setEnabled(subjectIsNotEmpty && !collectionComboboxEmpty);
}

void EventEdit::showEventEdit()
{
    mEventEdit->setFocus();
    QDateTime currentDateTime = QDateTime::currentDateTime();
    mStartDateTimeEdit->setDateTime(currentDateTime);
    mEndDateTimeEdit->setDateTime(currentDateTime.addSecs(3600));
    show();
}

void EventEdit::readConfig()
{
    const qint64 id = MessageViewer::MessageViewerSettingsBase::self()->lastEventSelectedFolder();
    if (id >= 0) {
        mCollectionCombobox->setDefaultCollection(Akonadi::Collection(id));
    }
}

Akonadi::Collection EventEdit::collection() const
{
    return mCollection;
}

void EventEdit::slotCollectionChanged(int /*index*/)
{
    setCollection(mCollectionCombobox->currentCollection());
}

void EventEdit::setCollection(const Akonadi::Collection &value)
{
    if (mCollection != value) {
        mCollection = value;
        Q_EMIT collectionChanged(mCollection);
    }
}

KMime::Message::Ptr EventEdit::message() const
{
    return mMessage;
}

void EventEdit::setMessage(const KMime::Message::Ptr &value)
{
    if (mMessage != value) {
        mMessage = value;
        const KMime::Headers::Subject *const subject = mMessage ? mMessage->subject(false) : nullptr;
        if (subject) {
            mEventEdit->setText(subject->asUnicodeString());
            mEventEdit->selectAll();
            mEventEdit->setFocus();
        } else {
            mEventEdit->clear();
        }
        Q_EMIT messageChanged(mMessage);
    }
}

void EventEdit::slotCloseWidget()
{
    if (isVisible()) {
        writeConfig();
        mEventEdit->clear();
        mMessage = KMime::Message::Ptr();
        hide();
    }
}

void EventEdit::slotReturnPressed()
{
    if (!mMessage) {
        qCDebug(CREATEEVENTPLUGIN_LOG) << " Message is null";
        return;
    }
    const Akonadi::Collection collection = mCollectionCombobox->currentCollection();
    if (!collection.isValid()) {
        qCDebug(CREATEEVENTPLUGIN_LOG) << " Collection is not valid";
        return;
    }

    const QDateTime dtstart = mStartDateTimeEdit->dateTime();
    const QDateTime dtend = mEndDateTimeEdit->dateTime();
    if (!dtstart.isValid() || !dtend.isValid()) {
        qCDebug(CREATEEVENTPLUGIN_LOG) << " date is not valid !";
        return;
    }

    if (!mEventEdit->text().trimmed().isEmpty()) {
        KCalCore::Event::Ptr event = createEventItem();
        Q_EMIT createEvent(event, collection);
        mEventEdit->clear();
        hide();
    }
}

bool EventEdit::eventFilter(QObject *object, QEvent *e)
{
    // Close the bar when pressing Escape.
    // Not using a QShortcut for this because it could conflict with
    // window-global actions (e.g. Emil Sedgh binds Esc to "close tab").
    // With a shortcut override we can catch this before it gets to kactions.
    const bool shortCutOverride = (e->type() == QEvent::ShortcutOverride);
    if (shortCutOverride) {
        QKeyEvent *kev = static_cast<QKeyEvent * >(e);
        if (kev->key() == Qt::Key_Escape) {
            e->accept();
            slotCloseWidget();
            return true;
        } else if (kev->key() == Qt::Key_Enter
                   || kev->key() == Qt::Key_Return
                   || kev->key() == Qt::Key_Space) {
            e->accept();
            if (object == mCollectionCombobox) {
                mCollectionCombobox->showPopup();
            }
            return true;
        }
    }
    return QWidget::eventFilter(object, e);
}

void EventEdit::slotEndDateTimeChanged(const QDateTime &newDateTime)
{
    if (!newDateTime.isValid()) {
        return;
    }
    QDateTime currentDateTime = QDateTime::currentDateTime();
    if (newDateTime.date() > currentDateTime.date()) {
        QDateTime newDateDate = newDateTime;
        newDateDate.setTime(QTime(0, 0, 0));
        mEndDateTimeEdit->setMinimumDateTime(newDateDate);
    }
}

void EventEdit::slotStartDateTimeChanged(const QDateTime &newDateTime)
{
    if (!newDateTime.isValid()) {
        return;
    }

    if (mEndDateTimeEdit->date() == newDateTime.date() && mEndDateTimeEdit->time() < newDateTime.time()) {
        mEndDateTimeEdit->setTime(newDateTime.time());
    }
    if (mEndDateTimeEdit->date() < newDateTime.date()) {
        mEndDateTimeEdit->setDate(newDateTime.date());
    }

    mEndDateTimeEdit->setMinimumDateTime(newDateTime);
}

KCalCore::Event::Ptr EventEdit::createEventItem()
{
    KCalCore::Attachment attachment(mMessage->encodedContent().toBase64(), KMime::Message::mimeType());
    const KMime::Headers::Subject *const subject = mMessage->subject(false);
    if (subject) {
        attachment.setLabel(subject->asUnicodeString());
    }
    KCalCore::Event::Ptr event(new KCalCore::Event);
    event->setSummary(mEventEdit->text());
    event->setDtStart(mStartDateTimeEdit->dateTime());
    event->setDtEnd(mEndDateTimeEdit->dateTime());
    event->addAttachment(attachment);
    return event;
}

void EventEdit::slotOpenEditor()
{
    KCalCore::Event::Ptr event = createEventItem();

    Akonadi::Item item;
    item.setPayload<KCalCore::Event::Ptr>(event);
    item.setMimeType(KCalCore::Event::eventMimeType());

    IncidenceEditorNG::IncidenceDialog *dlg = IncidenceEditorNG::IncidenceDialogFactory::create(true, KCalCore::IncidenceBase::TypeEvent, nullptr, this);
    connect(dlg, &IncidenceEditorNG::IncidenceDialog::finished, this, &EventEdit::slotCloseWidget);
    dlg->load(item);
    dlg->open();
}
