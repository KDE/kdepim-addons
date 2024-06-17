/*
  SPDX-FileCopyrightText: 2014 Sandro Knauß <knauss@kolabsys.com>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <Akonadi/Collection>
#include <Akonadi/Item>
#include <Akonadi/NoteUtils>
#include <KJob>

#include <KMime/Message>

class QObject;

namespace MessageViewer
{
class CreateNoteJob : public KJob
{
    Q_OBJECT
public:
    explicit CreateNoteJob(const KMime::Message::Ptr &notePtr, const Akonadi::Collection &collection, const Akonadi::Item &item, QObject *parent = nullptr);
    ~CreateNoteJob() override;

    void start() override;

private:
    void noteCreated(KJob *job);
    void noteUpdated(KJob *job);
    void relationCreated(KJob *job);

    const Akonadi::Item mItem;
    const Akonadi::Collection mCollection;
    Akonadi::NoteUtils::NoteMessageWrapper mNote;
};
}
