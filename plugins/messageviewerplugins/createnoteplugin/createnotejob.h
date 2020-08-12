/*
  SPDX-FileCopyrightText: 2014 Sandro Knauß <knauss@kolabsys.com>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef CREATENOTEJOB_H
#define CREATENOTEJOB_H

#include <KJob>
#include <AkonadiCore/Item>
#include <AkonadiCore/Collection>
#include <Akonadi/Notes/NoteUtils>

#include <kmime/kmime_message.h>

#include <QObject>

namespace MessageViewer {
class CreateNoteJob : public KJob
{
    Q_OBJECT
public:
    explicit CreateNoteJob(const KMime::Message::Ptr &notePtr, const Akonadi::Collection &collection, const Akonadi::Item &item, QObject *parent = nullptr);
    ~CreateNoteJob() override;

    void start() override;

private Q_SLOTS:
    void noteCreated(KJob *job);
    void noteUpdated(KJob *job);
    void relationCreated(KJob *job);

private:
    void createNote();
    Akonadi::Item mItem;
    Akonadi::Collection mCollection;
    Akonadi::NoteUtils::NoteMessageWrapper mNote;
};
}

#endif
