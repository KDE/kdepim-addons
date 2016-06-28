/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

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

#include "viewerplugincreatenoteinterface.h"
#include "noteedit.h"
#include "createnotejob.h"
#include "createnoteplugin_debug.h"
#include <KLocalizedString>
#include <KActionCollection>

#include <QLayout>
#include <QIcon>
#include <QAction>
#include <ItemFetchJob>
#include <ItemFetchScope>

using namespace MessageViewer;

ViewerPluginCreatenoteInterface::ViewerPluginCreatenoteInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    createAction(ac);
    mNoteEdit = new NoteEdit(parent);
    mNoteEdit->setObjectName(QStringLiteral("noteedit"));
    mNoteEdit->hide();
    connect(mNoteEdit, &NoteEdit::createNote, this, &ViewerPluginCreatenoteInterface::slotCreateNote);
    parent->layout()->addWidget(mNoteEdit);
}

ViewerPluginCreatenoteInterface::~ViewerPluginCreatenoteInterface()
{

}

void ViewerPluginCreatenoteInterface::setText(const QString &text)
{
    Q_UNUSED(text);
    //Nothing
}

QList<QAction *> ViewerPluginCreatenoteInterface::actions() const
{
    return mAction;
}

void ViewerPluginCreatenoteInterface::setMessage(const KMime::Message::Ptr &value)
{
    mNoteEdit->setMessage(value);
}

void ViewerPluginCreatenoteInterface::closePlugin()
{
    mNoteEdit->slotCloseWidget();
}

Akonadi::Relation ViewerPluginCreatenoteInterface::relatedNoteRelation() const
{
    Akonadi::Relation relation;
    foreach (const Akonadi::Relation &r, mMessageItem.relations()) {
        // assuming that GENERIC relations to emails are notes is a pretty horirific hack imo - aseigo
        if (r.type() == Akonadi::Relation::GENERIC && r.right().mimeType() == Akonadi::NoteUtils::noteMimeType()) {
            relation = r;
            break;
        }
    }
    return relation;
}

void ViewerPluginCreatenoteInterface::showWidget()
{
    if (!mMessageItem.relations().isEmpty())  {
        Akonadi::Relation relation = relatedNoteRelation();
        if (relation.isValid()) {
            Akonadi::ItemFetchJob *job = new Akonadi::ItemFetchJob(relation.right());
            job->fetchScope().fetchFullPayload(true);
            connect(job, &Akonadi::ItemFetchJob::result, this, &ViewerPluginCreatenoteInterface::slotNoteItemFetched);
            return;
        }
    }
    showCreateNewNoteWidget();
}

void ViewerPluginCreatenoteInterface::showCreateNewNoteWidget()
{
    mNoteEdit->showNoteEdit();
}

void ViewerPluginCreatenoteInterface::slotNoteItemFetched(KJob *job)
{
    if (job->error()) {
        qCDebug(CREATENOTEPLUGIN_LOG) << "There is not valid note:" << job->errorString();
        showCreateNewNoteWidget();
    } else {
        Akonadi::ItemFetchJob *fetch = qobject_cast<Akonadi::ItemFetchJob *>(job);
        Q_ASSERT(fetch);
        if (fetch->items().isEmpty() || !fetch->items().first().hasPayload<KMime::Message::Ptr>()) {
            showCreateNewNoteWidget();
        } else {
            Akonadi::NoteUtils::NoteMessageWrapper note(fetch->items().first().payload<KMime::Message::Ptr>());
            mNoteEdit->setMessage(note.message());
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
        QAction *act = new QAction(QIcon::fromTheme(QStringLiteral("view-pim-notes")), i18nc("create a new note out of this message", "Create Note"), this);
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
    CreateNoteJob *createJob = new CreateNoteJob(notePtr, collection, mMessageItem, this);
    createJob->start();
}
