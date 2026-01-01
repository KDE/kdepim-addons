/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "todoedit.h"
#include "createtodoplugin_debug.h"
#include <CalendarSupport/KCalPrefs>
#include <CalendarSupport/Utils>
#include <messageviewer/globalsettings_messageviewer.h>

#include <KLocalizedString>
#include <QIcon>
#include <QLineEdit>

#include <KMessageWidget>
#include <QEvent>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>

#include <Akonadi/CollectionComboBox>
#include <Akonadi/SpecialMailCollections>
#include <IncidenceEditor/IncidenceDialog>
#include <IncidenceEditor/IncidenceDialogFactory>
#include <KGuiItem>
#include <KStandardGuiItem>

namespace MessageViewer
{
QAbstractItemModel *_k_todoEditStubModel = nullptr;
}

using namespace MessageViewer;

TodoEdit::TodoEdit(QWidget *parent)
    : QWidget(parent)
    , mNoteEdit(new QLineEdit(this))
    , mMsgWidget(new KMessageWidget(this))
    , mSaveButton(new QPushButton(QIcon::fromTheme(QStringLiteral("task-new")), i18n("&Save"), this))
    , mOpenEditorButton(new QPushButton(i18nc("@action:button", "Open &Editor…"), this))
{
    auto vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(5, 5, 5, 5);
    vbox->setSpacing(2);

    mMsgWidget->setCloseButtonVisible(true);
    mMsgWidget->setMessageType(KMessageWidget::Positive);
    mMsgWidget->setObjectName(QLatin1StringView("msgwidget"));
    mMsgWidget->setWordWrap(true);
    mMsgWidget->setVisible(false);
    vbox->addWidget(mMsgWidget);

    auto hbox = new QHBoxLayout;
    hbox->setContentsMargins({});
    hbox->setSpacing(2);
    vbox->addLayout(hbox);

    auto lab = new QLabel(i18nc("@label:textbox", "To-do:"), this);
    hbox->addWidget(lab);

    mNoteEdit->setClearButtonEnabled(true);
    mNoteEdit->setObjectName(QLatin1StringView("noteedit"));
    mNoteEdit->setFocus();
    connect(mNoteEdit, &QLineEdit::textChanged, this, &TodoEdit::slotTextEdited);
    connect(mNoteEdit, &QLineEdit::returnPressed, this, &TodoEdit::slotReturnPressed);
    hbox->addWidget(mNoteEdit, 1);

    hbox->addSpacing(5);

    mCollectionCombobox = new Akonadi::CollectionComboBox(_k_todoEditStubModel, this);
    mCollectionCombobox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
    mCollectionCombobox->setMinimumWidth(250);
    mCollectionCombobox->setMimeTypeFilter(QStringList() << KCalendarCore::Todo::todoMimeType());
    mCollectionCombobox->setObjectName(QLatin1StringView("akonadicombobox"));
    connect(mCollectionCombobox->model(), &QAbstractItemModel::rowsInserted, this, &TodoEdit::comboboxRowInserted);
#ifndef QT_NO_ACCESSIBILITY
    mCollectionCombobox->setAccessibleDescription(i18n("Todo list where the new task will be stored."));
#endif
    mCollectionCombobox->setToolTip(i18nc("@info:tooltip", "Todo list where the new task will be stored"));
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::currentIndexChanged, this, &TodoEdit::slotCollectionChanged);
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::activated, this, &TodoEdit::slotCollectionChanged);
    hbox->addWidget(mCollectionCombobox);

    hbox = new QHBoxLayout;
    hbox->setContentsMargins({});
    hbox->setSpacing(2);
    vbox->addLayout(hbox);

    hbox->addStretch(1);
    mSaveButton->setObjectName(QLatin1StringView("save-button"));
    mSaveButton->setEnabled(false);
#ifndef QT_NO_ACCESSIBILITY
    mSaveButton->setAccessibleDescription(i18n("Create new todo and close this widget."));
#endif
    connect(mSaveButton, &QPushButton::clicked, this, &TodoEdit::slotReturnPressed);
    hbox->addWidget(mSaveButton);

    mOpenEditorButton->setObjectName(QLatin1StringView("open-editor-button"));
#ifndef QT_NO_ACCESSIBILITY
    mOpenEditorButton->setAccessibleDescription(i18n("Open todo editor, where more details can be changed."));
#endif
    mOpenEditorButton->setEnabled(false);
    connect(mOpenEditorButton, &QPushButton::clicked, this, &TodoEdit::slotOpenEditor);
    hbox->addWidget(mOpenEditorButton);

    auto btn = new QPushButton(this);
    KGuiItem::assign(btn, KStandardGuiItem::cancel());
    btn->setObjectName(QLatin1StringView("close-button"));
#ifndef QT_NO_ACCESSIBILITY
    btn->setAccessibleDescription(i18n("Close the widget for creating new todos."));
#endif
    connect(btn, &QPushButton::clicked, this, &TodoEdit::slotCloseWidget);
    hbox->addWidget(btn);

    readConfig();
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    mCollectionCombobox->installEventFilter(this);
    installEventFilter(this);
}

TodoEdit::~TodoEdit()
{
    writeConfig();
}

void TodoEdit::comboboxRowInserted()
{
    updateButtons(mNoteEdit->text());
}

void TodoEdit::updateButtons(const QString &subject)
{
    const bool subjectIsNotEmpty = !subject.trimmed().isEmpty();
    const bool collectionComboboxEmpty = (mCollectionCombobox->count() < 1);
    mSaveButton->setEnabled(subjectIsNotEmpty && !collectionComboboxEmpty);
    mOpenEditorButton->setEnabled(subjectIsNotEmpty && !collectionComboboxEmpty);
}

void TodoEdit::showToDoWidget()
{
    const KMime::Headers::Subject *const subject = mMessage ? mMessage->subject(KMime::CreatePolicy::DontCreate) : nullptr;
    if (subject) {
        bool isSentFolder = false;
        if (mCurrentCollection.isValid()) {
            isSentFolder = (Akonadi::SpecialMailCollections::self()->defaultCollection(Akonadi::SpecialMailCollections::SentMail) == mCurrentCollection);
        }
        mNoteEdit->setText(isSentFolder ? i18n("Check I received a reply about \"%1\"", subject->asUnicodeString())
                                        : i18n("Reply to \"%1\"", subject->asUnicodeString()));
        mNoteEdit->selectAll();
        mNoteEdit->setFocus();
    } else {
        mNoteEdit->clear();
    }
    mNoteEdit->setFocus();
    show();
}

void TodoEdit::setCurrentCollection(const Akonadi::Collection &col)
{
    mCurrentCollection = col;
}

void TodoEdit::writeConfig()
{
    const Akonadi::Collection col = mCollectionCombobox->currentCollection();
    // col might not be valid if the collection wasn't found yet (the combo is async), skip saving in that case
    if (col.isValid() && col.id() != MessageViewer::MessageViewerSettingsBase::self()->lastSelectedFolder()) {
        MessageViewer::MessageViewerSettingsBase::self()->setLastSelectedFolder(col.id());
        MessageViewer::MessageViewerSettingsBase::self()->save();
    }
}

void TodoEdit::readConfig()
{
    const qint64 id = MessageViewer::MessageViewerSettingsBase::self()->lastSelectedFolder();
    if (id != -1) {
        mCollectionCombobox->setDefaultCollection(Akonadi::Collection(id));
    }
}

Akonadi::Collection TodoEdit::collection() const
{
    return mCollection;
}

void TodoEdit::slotCollectionChanged(int /*index*/)
{
    setCollection(mCollectionCombobox->currentCollection());
}

void TodoEdit::setCollection(const Akonadi::Collection &value)
{
    if (mCollection != value) {
        mCollection = value;
        Q_EMIT collectionChanged(mCollection);
    }
}

std::shared_ptr<KMime::Message> TodoEdit::message() const
{
    return mMessage;
}

void TodoEdit::setMessage(const std::shared_ptr<KMime::Message> &value)
{
    if (mMessage != value) {
        mMessage = value;
        Q_EMIT messageChanged(mMessage);
    }
}

void TodoEdit::slotCloseWidget()
{
    if (isVisible()) {
        writeConfig();
        mNoteEdit->clear();
        mMessage = std::shared_ptr<KMime::Message>();
        mMsgWidget->hide();
        hide();
    }
}

void TodoEdit::slotReturnPressed()
{
    if (!mMessage) {
        qCDebug(CREATETODOPLUGIN_LOG) << " Message is null";
        return;
    }
    const Akonadi::Collection currentCollection = mCollectionCombobox->currentCollection();
    if (!currentCollection.isValid()) {
        qCDebug(CREATETODOPLUGIN_LOG) << " Collection is not valid";
        return;
    }

    if (!mNoteEdit->text().trimmed().isEmpty()) {
        mMsgWidget->setText(i18nc("%1 is summary of the todo, %2 is name of the folder in which it is stored",
                                  "New todo '%1' was added to task list '%2'",
                                  mNoteEdit->text(),
                                  currentCollection.displayName()));
        KCalendarCore::Todo::Ptr todo = createTodoItem();

        // We don't hide the widget here, so that multiple todo's can be added
        Q_EMIT createTodo(todo, currentCollection);

        mMsgWidget->animatedShow();
    }
}

KCalendarCore::Todo::Ptr TodoEdit::createTodoItem()
{
    if (mMessage) {
        KCalendarCore::Todo::Ptr todo(new KCalendarCore::Todo);
        todo->setSummary(mNoteEdit->text());
        KCalendarCore::Attachment attachment(mMessage->encodedContent().toBase64(), KMime::Message::mimeType());
        const KMime::Headers::Subject *const subject = mMessage->subject(KMime::CreatePolicy::DontCreate);
        if (subject) {
            attachment.setLabel(subject->asUnicodeString());
        }
        if (CalendarSupport::KCalPrefs::instance()->defaultTodoReminders()) {
            KCalendarCore::Alarm::Ptr alm = todo->newAlarm();
            CalendarSupport::createAlarmReminder(alm, todo->type());
        }

        todo->addAttachment(attachment);
        return todo;
    }
    return {};
}

bool TodoEdit::eventFilter(QObject *object, QEvent *e)
{
    // Close the bar when pressing Escape.
    // Not using a QShortcut for this because it could conflict with
    // window-global actions (e.g. Emil Sedgh binds Esc to "close tab").
    // With a shortcut override we can catch this before it gets to kactions.
    const bool shortCutOverride = (e->type() == QEvent::ShortcutOverride);
    if (shortCutOverride || e->type() == QEvent::KeyPress) {
        auto kev = static_cast<QKeyEvent *>(e);
        if (kev->key() == Qt::Key_Escape) {
            e->accept();
            slotCloseWidget();
            return true;
        } else if (kev->key() == Qt::Key_Enter || kev->key() == Qt::Key_Return || kev->key() == Qt::Key_Space) {
            e->accept();
            if (shortCutOverride) {
                return true;
            }
            if (object == mCollectionCombobox) {
                mCollectionCombobox->showPopup();
                return true;
            }
        }
    }
    return QWidget::eventFilter(object, e);
}

void TodoEdit::slotOpenEditor()
{
    KCalendarCore::Todo::Ptr event = createTodoItem();
    if (event) {
        Akonadi::Item item;
        item.setPayload<KCalendarCore::Todo::Ptr>(event);
        item.setMimeType(KCalendarCore::Todo::todoMimeType());

        IncidenceEditorNG::IncidenceDialog *dlg =
            IncidenceEditorNG::IncidenceDialogFactory::create(true, KCalendarCore::IncidenceBase::TypeTodo, nullptr, this);
        dlg->selectCollection(mCollectionCombobox->currentCollection());
        connect(dlg, &IncidenceEditorNG::IncidenceDialog::finished, this, &TodoEdit::slotCloseWidget);
        dlg->load(item);
        dlg->open();
    }
}

void TodoEdit::slotTextEdited(const QString &subject)
{
    updateButtons(subject);
    if (mMsgWidget->isVisible()) {
        mMsgWidget->hide();
    }
}

#include "moc_todoedit.cpp"
