/*
   Copyright (C) 2014-2017 Montel Laurent <montel@kde.org>

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

#include "todoedit.h"
#include "globalsettings_messageviewer.h"
#include "createtodoplugin_debug.h"
#include <KLocalizedString>
#include <QLineEdit>
#include <QIcon>

#include <KMessageWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include <QLabel>

#include <AkonadiWidgets/CollectionComboBox>

#include <IncidenceEditor/IncidenceDialog>
#include <IncidenceEditor/IncidenceDialogFactory>
#include <akonadi/kmime/specialmailcollections.h>
#include <KGuiItem>
#include <KStandardGuiItem>

namespace MessageViewer {
QAbstractItemModel *_k_todoEditStubModel = nullptr;
}

using namespace MessageViewer;

TodoEdit::TodoEdit(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setMargin(5);
    vbox->setSpacing(2);

    mMsgWidget = new KMessageWidget(this);
    mMsgWidget->setCloseButtonVisible(true);
    mMsgWidget->setMessageType(KMessageWidget::Positive);
    mMsgWidget->setObjectName(QStringLiteral("msgwidget"));
    mMsgWidget->setWordWrap(true);
    mMsgWidget->setVisible(false);
    vbox->addWidget(mMsgWidget);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->setMargin(0);
    hbox->setSpacing(2);
    vbox->addLayout(hbox);

    QLabel *lab = new QLabel(i18n("Todo:"), this);
    hbox->addWidget(lab);

    mNoteEdit = new QLineEdit(this);
    mNoteEdit->setClearButtonEnabled(true);
    mNoteEdit->setObjectName(QStringLiteral("noteedit"));
    mNoteEdit->setFocus();
    connect(mNoteEdit, &QLineEdit::textChanged, this, &TodoEdit::slotTextEdited);
    connect(mNoteEdit, &QLineEdit::returnPressed, this, &TodoEdit::slotReturnPressed);
    hbox->addWidget(mNoteEdit, 1);

    hbox->addSpacing(5);

    mCollectionCombobox = new Akonadi::CollectionComboBox(_k_todoEditStubModel, this);
    mCollectionCombobox->setAccessRightsFilter(Akonadi::Collection::CanCreateItem);
    mCollectionCombobox->setMinimumWidth(250);
    mCollectionCombobox->setMimeTypeFilter(QStringList() << KCalCore::Todo::todoMimeType());
    mCollectionCombobox->setObjectName(QStringLiteral("akonadicombobox"));
    connect(mCollectionCombobox->model(), &QAbstractItemModel::rowsInserted, this, &TodoEdit::comboboxRowInserted);
#ifndef QT_NO_ACCESSIBILITY
    mCollectionCombobox->setAccessibleDescription(i18n("Todo list where the new task will be stored."));
#endif
    mCollectionCombobox->setToolTip(i18n("Todo list where the new task will be stored"));
    connect(mCollectionCombobox, QOverload<int>::of(&Akonadi::CollectionComboBox::currentIndexChanged), this, &TodoEdit::slotCollectionChanged);
    connect(mCollectionCombobox, QOverload<int>::of(&Akonadi::CollectionComboBox::activated), this, &TodoEdit::slotCollectionChanged);
    hbox->addWidget(mCollectionCombobox);

    hbox = new QHBoxLayout;
    hbox->setMargin(0);
    hbox->setSpacing(2);
    vbox->addLayout(hbox);

    hbox->addStretch(1);
    mSaveButton = new QPushButton(QIcon::fromTheme(QStringLiteral("task-new")), i18n("&Save"), this);
    mSaveButton->setObjectName(QStringLiteral("save-button"));
    mSaveButton->setEnabled(false);
#ifndef QT_NO_ACCESSIBILITY
    mSaveButton->setAccessibleDescription(i18n("Create new todo and close this widget."));
#endif
    connect(mSaveButton, &QPushButton::clicked, this, &TodoEdit::slotReturnPressed);
    hbox->addWidget(mSaveButton);

    mOpenEditorButton = new QPushButton(i18n("Open &editor..."), this);
    mOpenEditorButton->setObjectName(QStringLiteral("open-editor-button"));
#ifndef QT_NO_ACCESSIBILITY
    mOpenEditorButton->setAccessibleDescription(i18n("Open todo editor, where more details can be changed."));
#endif
    mOpenEditorButton->setEnabled(false);
    connect(mOpenEditorButton, &QPushButton::clicked, this, &TodoEdit::slotOpenEditor);
    hbox->addWidget(mOpenEditorButton);

    QPushButton *btn = new QPushButton(this);
    KGuiItem::assign(btn, KStandardGuiItem::cancel());
    btn->setObjectName(QStringLiteral("close-button"));
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
    const KMime::Headers::Subject *const subject = mMessage ? mMessage->subject(false) : nullptr;
    if (subject) {
        bool isSentFolder = false;
        if (mCurrentCollection.isValid()) {
            isSentFolder = (Akonadi::SpecialMailCollections::self()->defaultCollection(Akonadi::SpecialMailCollections::SentMail) == mCurrentCollection);
        }
        mNoteEdit->setText(isSentFolder ? i18n("Check I received a reply about \"%1\"", subject->asUnicodeString()) : i18n("Reply to \"%1\"", subject->asUnicodeString()));
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

KMime::Message::Ptr TodoEdit::message() const
{
    return mMessage;
}

void TodoEdit::setMessage(const KMime::Message::Ptr &value)
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
        mMessage = KMime::Message::Ptr();
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
    const Akonadi::Collection collection = mCollectionCombobox->currentCollection();
    if (!collection.isValid()) {
        qCDebug(CREATETODOPLUGIN_LOG) << " Collection is not valid";
        return;
    }

    if (!mNoteEdit->text().trimmed().isEmpty()) {
        mMsgWidget->setText(i18nc("%1 is summary of the todo, %2 is name of the folder in which it is stored",
                                  "New todo '%1' was added to task list '%2'", mNoteEdit->text(), collection.displayName()));
        KCalCore::Todo::Ptr todo = createTodoItem();
        mNoteEdit->clear();

        // We don't hide the widget here, so that multiple todo's can be added
        Q_EMIT createTodo(todo, collection);

        mMsgWidget->animatedShow();
    }
}

KCalCore::Todo::Ptr TodoEdit::createTodoItem()
{
    KCalCore::Todo::Ptr todo(new KCalCore::Todo);
    todo->setSummary(mNoteEdit->text());
    KCalCore::Attachment::Ptr attachment(new KCalCore::Attachment(mMessage->encodedContent().toBase64(), KMime::Message::mimeType()));
    const KMime::Headers::Subject *const subject = mMessage->subject(false);
    if (subject) {
        attachment->setLabel(subject->asUnicodeString());
    }

    todo->addAttachment(attachment);
    return todo;
}

bool TodoEdit::eventFilter(QObject *object, QEvent *e)
{
    // Close the bar when pressing Escape.
    // Not using a QShortcut for this because it could conflict with
    // window-global actions (e.g. Emil Sedgh binds Esc to "close tab").
    // With a shortcut override we can catch this before it gets to kactions.
    const bool shortCutOverride = (e->type() == QEvent::ShortcutOverride);
    if (shortCutOverride || e->type() == QEvent::KeyPress) {
        QKeyEvent *kev = static_cast<QKeyEvent * >(e);
        if (kev->key() == Qt::Key_Escape) {
            e->accept();
            slotCloseWidget();
            return true;
        } else if (kev->key() == Qt::Key_Enter
                   || kev->key() == Qt::Key_Return
                   || kev->key() == Qt::Key_Space) {
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
    KCalCore::Todo::Ptr event = createTodoItem();

    Akonadi::Item item;
    item.setPayload<KCalCore::Todo::Ptr>(event);
    item.setMimeType(KCalCore::Todo::todoMimeType());

    IncidenceEditorNG::IncidenceDialog *dlg = IncidenceEditorNG::IncidenceDialogFactory::create(true, KCalCore::IncidenceBase::TypeTodo, nullptr, this);
    connect(dlg, &IncidenceEditorNG::IncidenceDialog::finished, this, &TodoEdit::slotCloseWidget);
    dlg->load(item);
    dlg->open();
}

void TodoEdit::slotTextEdited(const QString &subject)
{
    updateButtons(subject);
    if (mMsgWidget->isVisible()) {
        mMsgWidget->hide();
    }
}
