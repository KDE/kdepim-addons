/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreatenoteinterface.h"
#include "createnotejob.h"
#include "createnoteplugin_debug.h"
#include "noteedit.h"
#include <KActionCollection>
#include <KLocalizedString>

#include <Akonadi/ItemFetchJob>
#include <Akonadi/ItemFetchScope>
#include <QAction>
#include <QIcon>
#include <QLayout>

using namespace MessageViewer;

ViewerPluginCreatenoteInterface::ViewerPluginCreatenoteInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    createAction(ac);
}

ViewerPluginCreatenoteInterface::~ViewerPluginCreatenoteInterface() = default;

void ViewerPluginCreatenoteInterface::setText(const QString &text)
{
    Q_UNUSED(text)
    // Nothing
}

QList<QAction *> ViewerPluginCreatenoteInterface::actions() const
{
    return mAction;
}

void ViewerPluginCreatenoteInterface::setMessage(const KMime::Message::Ptr &value)
{
    widget()->setMessage(value);
}

void ViewerPluginCreatenoteInterface::closePlugin()
{
    if (mNoteEdit) {
        mNoteEdit->slotCloseWidget();
    }
}

Akonadi::Relation ViewerPluginCreatenoteInterface::relatedNoteRelation() const
{
    Akonadi::Relation relation;
    const auto relations = mMessageItem.relations();
    for (const Akonadi::Relation &r : relations) {
        // assuming that GENERIC relations to emails are notes is a pretty horrific hack imo - aseigo
        if (r.type() == Akonadi::Relation::GENERIC && r.right().mimeType() == Akonadi::NoteUtils::noteMimeType()) {
            relation = r;
            break;
        }
    }
    return relation;
}

void ViewerPluginCreatenoteInterface::showWidget()
{
    if (!mMessageItem.relations().isEmpty()) {
        Akonadi::Relation relation = relatedNoteRelation();
        if (relation.isValid()) {
            auto job = new Akonadi::ItemFetchJob(relation.right());
            job->fetchScope().fetchFullPayload(true);
            connect(job, &Akonadi::ItemFetchJob::result, this, &ViewerPluginCreatenoteInterface::slotNoteItemFetched);
            return;
        }
    }
    showCreateNewNoteWidget();
}

void ViewerPluginCreatenoteInterface::showCreateNewNoteWidget()
{
    widget()->showNoteEdit();
}

void ViewerPluginCreatenoteInterface::slotNoteItemFetched(KJob *job)
{
    if (job->error()) {
        qCDebug(CREATENOTEPLUGIN_LOG) << "There is not valid note:" << job->errorString();
        showCreateNewNoteWidget();
    } else {
        auto fetch = qobject_cast<Akonadi::ItemFetchJob *>(job);
        Q_ASSERT(fetch);
        if (fetch->items().isEmpty() || !fetch->items().constFirst().hasPayload<KMime::Message::Ptr>()) {
            showCreateNewNoteWidget();
        } else {
            Akonadi::NoteUtils::NoteMessageWrapper note(fetch->items().constFirst().payload<KMime::Message::Ptr>());
            widget()->setMessage(note.message());
            showCreateNewNoteWidget();
        }
    }
}

void ViewerPluginCreatenoteInterface::setMessageItem(const Akonadi::Item &item)
{
    mMessageItem = item;
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginCreatenoteInterface::featureTypes() const
{
    return ViewerPluginInterface::NeedMessage;
}

void ViewerPluginCreatenoteInterface::updateAction(const Akonadi::Item &item)
{
    mMessageItem = item;
    if (!mAction.isEmpty()) {
        QString createNoteText;
        if (relatedNoteRelation().isValid()) {
            createNoteText = i18nc("edit a note on this message", "Edit Note");
        } else {
            createNoteText = i18nc("create a new note out of this message", "Create Note");
        }

        mAction.at(0)->setText(createNoteText);
        mAction.at(0)->setIconText(createNoteText);
    }
}

void ViewerPluginCreatenoteInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        auto act = new QAction(QIcon::fromTheme(QStringLiteral("view-pim-notes")), i18nc("create a new note out of this message", "Create Note"), this);
        act->setIconText(i18nc("create a new note out of this message", "Create Note"));
        addHelpTextAction(act, i18n("Allows you to create a note from this message"));
        act->setWhatsThis(i18n("This option starts an editor to create a note. Then you can edit the note to your liking before saving it."));
        ac->addAction(QStringLiteral("create_note"), act);
        connect(act, &QAction::triggered, this, &ViewerPluginCreatenoteInterface::slotActivatePlugin);
        mAction.append(act);
    }
}

void ViewerPluginCreatenoteInterface::slotCreateNote(const KMime::Message::Ptr &notePtr, const Akonadi::Collection &collection)
{
    auto createJob = new CreateNoteJob(notePtr, collection, mMessageItem, this);
    createJob->start();
}

NoteEdit *ViewerPluginCreatenoteInterface::widget()
{
    if (!mNoteEdit) {
        auto parentWidget = static_cast<QWidget *>(parent());
        mNoteEdit = new NoteEdit(parentWidget);
        connect(mNoteEdit, &NoteEdit::createNote, this, &ViewerPluginCreatenoteInterface::slotCreateNote);
        mNoteEdit->setObjectName(QStringLiteral("noteedit"));
        parentWidget->layout()->addWidget(mNoteEdit);
        mNoteEdit->hide();
    }
    return mNoteEdit;
}
