/*
  SPDX-FileCopyrightText: 2014 Sandro Knauß <knauss@kolabsys.com>*

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "noteedit.h"
#include "createnoteplugin_debug.h"
#include <IncidenceEditor/IncidenceDialog>
#include <IncidenceEditor/IncidenceDialogFactory>
#include <messageviewer/globalsettings_messageviewer.h>

#include <Akonadi/CollectionComboBox>

#include <KGuiItem>
#include <KLocalizedString>
#include <KStandardGuiItem>

#include <QEvent>
#include <QHBoxLayout>
#include <QIcon>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace MessageViewer
{
QAbstractItemModel *_k_noteEditStubModel = nullptr;
}

using namespace MessageViewer;

NoteEdit::NoteEdit(QWidget *parent)
    : QWidget(parent)
    , mNoteEdit(new QLineEdit(this))
    , mCollectionCombobox(new Akonadi::CollectionComboBox(_k_noteEditStubModel, this))
    , mSaveButton(new QPushButton(QIcon::fromTheme(QStringLiteral("view-pim-notes")), i18n("&Save"), this))
{
    auto vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(5, 5, 5, 5);
    vbox->setSpacing(2);

    auto hbox = new QHBoxLayout;
    hbox->setContentsMargins({});
    hbox->setSpacing(2);
    vbox->addLayout(hbox);

    auto lab = new QLabel(i18n("Note:"), this);
    hbox->addWidget(lab);

    mNoteEdit->setClearButtonEnabled(true);
    mNoteEdit->setObjectName(QLatin1StringView("noteedit"));
    mNoteEdit->setFocus();
    connect(mNoteEdit, &QLineEdit::returnPressed, this, &NoteEdit::slotReturnPressed);
    connect(mNoteEdit, &QLineEdit::textChanged, this, &NoteEdit::slotUpdateButtons);
    hbox->addWidget(mNoteEdit);

    hbox->addSpacing(5);

    mCollectionCombobox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
    mCollectionCombobox->setMinimumWidth(250);
    mCollectionCombobox->setMimeTypeFilter(QStringList() << Akonadi::NoteUtils::noteMimeType());
    mCollectionCombobox->setObjectName(QLatin1StringView("akonadicombobox"));
#ifndef QT_NO_ACCESSIBILITY
    mCollectionCombobox->setAccessibleDescription(i18n("Calendar where the new event will be stored."));
#endif
    mCollectionCombobox->setToolTip(i18n("Calendar where the new event will be stored"));
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::currentIndexChanged, this, &NoteEdit::slotCollectionChanged);
    connect(mCollectionCombobox, &Akonadi::CollectionComboBox::activated, this, &NoteEdit::slotCollectionChanged);
    hbox->addWidget(mCollectionCombobox);

    hbox = new QHBoxLayout;
    hbox->setContentsMargins({});
    hbox->setSpacing(2);
    vbox->addLayout(hbox);

    hbox->addStretch(1);

    hbox = new QHBoxLayout;
    hbox->setSpacing(2);
    hbox->setContentsMargins({});
    vbox->addLayout(hbox);

    hbox->addStretch(1);

    mSaveButton->setObjectName(QLatin1StringView("save-button"));
    mSaveButton->setEnabled(false);
#ifndef QT_NO_ACCESSIBILITY
    mSaveButton->setAccessibleDescription(i18n("Create new note and close this widget."));
#endif
    connect(mSaveButton, &QPushButton::clicked, this, &NoteEdit::slotReturnPressed);
    hbox->addWidget(mSaveButton);

    auto btn = new QPushButton(this);
    KGuiItem::assign(btn, KStandardGuiItem::cancel());
    btn->setObjectName(QLatin1StringView("close-button"));
#ifndef QT_NO_ACCESSIBILITY
    btn->setAccessibleDescription(i18n("Close the widget for creating new notes."));
#endif
    connect(btn, &QPushButton::clicked, this, &NoteEdit::slotCloseWidget);
    hbox->addWidget(btn);

    readConfig();
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed));
    installEventFilter(this);
    mCollectionCombobox->installEventFilter(this);
}

NoteEdit::~NoteEdit()
{
    writeConfig();
}

void NoteEdit::writeConfig()
{
    if (mCollectionCombobox->currentCollection().id() != MessageViewer::MessageViewerSettingsBase::self()->lastNoteSelectedFolder()) {
        MessageViewer::MessageViewerSettingsBase::self()->setLastNoteSelectedFolder(mCollectionCombobox->currentCollection().id());
        MessageViewer::MessageViewerSettingsBase::self()->save();
    }
}

void NoteEdit::slotUpdateButtons(const QString &subject)
{
    const bool subjectIsNotEmpty = !subject.trimmed().isEmpty();
    mSaveButton->setEnabled(subjectIsNotEmpty);
}

void NoteEdit::showNoteEdit()
{
    mNoteEdit->setFocus();
    show();
}

void NoteEdit::readConfig()
{
    const qint64 id = MessageViewer::MessageViewerSettingsBase::self()->lastNoteSelectedFolder();
    if (id != -1) {
        mCollectionCombobox->setDefaultCollection(Akonadi::Collection(id));
    }
}

Akonadi::Collection NoteEdit::collection() const
{
    return mCollection;
}

void NoteEdit::slotCollectionChanged(int /*index*/)
{
    setCollection(mCollectionCombobox->currentCollection());
}

void NoteEdit::setCollection(const Akonadi::Collection &value)
{
    if (mCollection != value) {
        mCollection = value;
        Q_EMIT collectionChanged(mCollection);
    }
}

KMime::Message::Ptr NoteEdit::message() const
{
    return mMessage;
}

void NoteEdit::setMessage(const KMime::Message::Ptr &value)
{
    if (mMessage != value) {
        mMessage = value;
        const KMime::Headers::Subject *const subject = mMessage ? mMessage->subject(false) : nullptr;
        if (subject) {
            mNoteEdit->setText(subject->asUnicodeString());
            mNoteEdit->selectAll();
            mNoteEdit->setFocus();
        } else {
            mNoteEdit->clear();
        }
        Q_EMIT messageChanged(mMessage);
    }
}

void NoteEdit::slotCloseWidget()
{
    writeConfig();
    mNoteEdit->clear();
    mMessage = KMime::Message::Ptr();
    hide();
}

void NoteEdit::slotReturnPressed()
{
    if (!mMessage) {
        qCDebug(CREATENOTEPLUGIN_LOG) << " Message is null";
        return;
    }
    const Akonadi::Collection collection = mCollectionCombobox->currentCollection();
    if (!collection.isValid()) {
        qCDebug(CREATENOTEPLUGIN_LOG) << " Collection is not valid";
        return;
    }

    if (!mNoteEdit->text().trimmed().isEmpty()) {
        Akonadi::NoteUtils::NoteMessageWrapper note;
        note.setTitle(mNoteEdit->text());
        Q_EMIT createNote(note.message(), collection);
        mNoteEdit->clear();
        hide();
    }
}

bool NoteEdit::eventFilter(QObject *object, QEvent *e)
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

#include "moc_noteedit.cpp"
