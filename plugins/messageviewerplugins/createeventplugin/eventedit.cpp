/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "eventedit.h"
#include "createeventplugin_debug.h"
#include "eventdatetimewidget.h"
#include <CalendarSupport/KCalPrefs>
#include <CalendarSupport/Utils>
#include <messageviewer/globalsettings_messageviewer.h>

#include <KLocalizedString>
#include <QDateTime>
#include <QIcon>
#include <QLineEdit>

#include <QEvent>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>

#include <Akonadi/CollectionComboBox>
#include <QPushButton>

#include <IncidenceEditor/IncidenceDialog>
#include <IncidenceEditor/IncidenceDialogFactory>
#include <KGuiItem>
#include <KStandardGuiItem>

namespace MessageViewer
{
QAbstractItemModel *_k_eventEditStubModel = nullptr;
}

using namespace MessageViewer;

EventEdit::EventEdit(QWidget *parent)
    : QWidget(parent)
    , mEventEdit(new QLineEdit(this))
    , mStartDateTimeEdit(new EventDateTimeWidget(this))
    , mEndDateTimeEdit(new EventDateTimeWidget(this))
    , mSaveButton(new QPushButton(QIcon::fromTheme(QStringLiteral("appointment-new")), i18n("&Save"), this))
    , mOpenEditorButton(new QPushButton(i18n("Open &Editor..."), this))
{
    auto vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(5, 5, 5, 5);
    vbox->setSpacing(2);

    auto hbox = new QHBoxLayout;
    hbox->setContentsMargins({});
    hbox->setSpacing(2);
    vbox->addLayout(hbox);

    auto lab = new QLabel(i18n("Event:"), this);
    hbox->addWidget(lab);

    mEventEdit->setClearButtonEnabled(true);
    mEventEdit->setObjectName(QLatin1StringView("eventedit"));
    mEventEdit->setFocus();
    connect(mEventEdit, &QLineEdit::returnPressed, this, &EventEdit::slotReturnPressed);
    connect(mEventEdit, &QLineEdit::textChanged, this, &EventEdit::slotUpdateButtons);
    hbox->addWidget(mEventEdit);

    hbox->addSpacing(5);

    mCollectionCombobox = new Akonadi::CollectionComboBox(_k_eventEditStubModel, this);
    mCollectionCombobox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
    mCollectionCombobox->setMinimumWidth(250);
    mCollectionCombobox->setMimeTypeFilter(QStringList() << KCalendarCore::Event::eventMimeType());
    mCollectionCombobox->setObjectName(QLatin1StringView("akonadicombobox"));
#ifndef QT_NO_ACCESSIBILITY
    mCollectionCombobox->setAccessibleDescription(i18n("Calendar where the new event will be stored."));
#endif
    mCollectionCombobox->setToolTip(i18n("Calendar where the new event will be stored"));

    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::currentIndexChanged, this, &EventEdit::slotCollectionChanged);
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::activated, this, &EventEdit::slotCollectionChanged);

    connect(mCollectionCombobox->model(), &QAbstractItemModel::rowsInserted, this, &EventEdit::comboboxRowInserted);
    hbox->addWidget(mCollectionCombobox);

    hbox = new QHBoxLayout;
    hbox->setContentsMargins({});
    hbox->setSpacing(2);
    vbox->addLayout(hbox);

    lab = new QLabel(i18n("Start:"), this);
    hbox->addWidget(lab);
    QDateTime currentDateTime = QDateTime::currentDateTime();
    mStartDateTimeEdit->setObjectName(QLatin1StringView("startdatetimeedit"));
    mStartDateTimeEdit->setDateTime(currentDateTime);
#ifndef QT_NO_ACCESSIBILITY
    mStartDateTimeEdit->setAccessibleDescription(i18n("Select start time for event."));
#endif
    connect(mStartDateTimeEdit, &EventDateTimeWidget::dateTimeChanged, this, &EventEdit::slotStartDateTimeChanged);
    hbox->addWidget(mStartDateTimeEdit);

    hbox->addSpacing(5);

    lab = new QLabel(i18n("End:"), this);
    hbox->addWidget(lab);
    mEndDateTimeEdit->setObjectName(QLatin1StringView("enddatetimeedit"));
    mEndDateTimeEdit->setDateTime(currentDateTime.addSecs(3600));
#ifndef QT_NO_ACCESSIBILITY
    mEndDateTimeEdit->setAccessibleDescription(i18n("Select end time for event."));
#endif
    connect(mEndDateTimeEdit, &EventDateTimeWidget::dateTimeChanged, this, &EventEdit::slotEndDateTimeChanged);

    hbox->addWidget(mEndDateTimeEdit);

    hbox->addStretch(1);

    hbox = new QHBoxLayout;
    hbox->setSpacing(2);
    hbox->setContentsMargins({});
    vbox->addLayout(hbox);

    hbox->addStretch(1);

    mSaveButton->setObjectName(QLatin1StringView("save-button"));
    mSaveButton->setEnabled(false);
#ifndef QT_NO_ACCESSIBILITY
    mSaveButton->setAccessibleDescription(i18n("Create new event and close this widget."));
#endif
    connect(mSaveButton, &QPushButton::clicked, this, &EventEdit::slotReturnPressed);
    hbox->addWidget(mSaveButton);

#ifndef QT_NO_ACCESSIBILITY
    mOpenEditorButton->setAccessibleDescription(i18n("Open event editor, where more details can be changed."));
#endif
    mOpenEditorButton->setObjectName(QLatin1StringView("open-editor-button"));
    mOpenEditorButton->setEnabled(false);
    connect(mOpenEditorButton, &QPushButton::clicked, this, &EventEdit::slotOpenEditor);
    hbox->addWidget(mOpenEditorButton);

    auto btn = new QPushButton(this);
    KGuiItem::assign(btn, KStandardGuiItem::cancel());
    btn->setObjectName(QLatin1StringView("close-button"));
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
        KCalendarCore::Event::Ptr event = createEventItem();
        Q_EMIT createEvent(event, collection);
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
        auto kev = static_cast<QKeyEvent *>(e);
        if (kev->key() == Qt::Key_Escape) {
            e->accept();
            slotCloseWidget();
            return true;
        } else if (kev->key() == Qt::Key_Enter || kev->key() == Qt::Key_Return || kev->key() == Qt::Key_Space) {
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

KCalendarCore::Event::Ptr EventEdit::createEventItem()
{
    if (mMessage) {
        KCalendarCore::Attachment attachment(mMessage->encodedContent().toBase64(), KMime::Message::mimeType());
        const KMime::Headers::Subject *const subject = mMessage->subject(false);
        if (subject) {
            attachment.setLabel(subject->asUnicodeString());
        }
        KCalendarCore::Event::Ptr event(new KCalendarCore::Event);
        event->setSummary(mEventEdit->text());
        event->setDtStart(mStartDateTimeEdit->dateTime());
        event->setDtEnd(mEndDateTimeEdit->dateTime());
        event->addAttachment(attachment);

        if (CalendarSupport::KCalPrefs::instance()->defaultEventReminders()) {
            KCalendarCore::Alarm::Ptr alm = event->newAlarm();
            CalendarSupport::createAlarmReminder(alm, event->type());
        }

        return event;
    }
    return {};
}

void EventEdit::slotOpenEditor()
{
    KCalendarCore::Event::Ptr event = createEventItem();
    if (event) {
        Akonadi::Item item;
        item.setPayload<KCalendarCore::Event::Ptr>(event);
        item.setMimeType(KCalendarCore::Event::eventMimeType());

        IncidenceEditorNG::IncidenceDialog *dlg =
            IncidenceEditorNG::IncidenceDialogFactory::create(true, KCalendarCore::IncidenceBase::TypeEvent, nullptr, this);
        dlg->selectCollection(mCollectionCombobox->currentCollection());
        connect(dlg, &IncidenceEditorNG::IncidenceDialog::finished, this, &EventEdit::slotCloseWidget);
        dlg->load(item);
        dlg->open();
    }
}

#include "moc_eventedit.cpp"
