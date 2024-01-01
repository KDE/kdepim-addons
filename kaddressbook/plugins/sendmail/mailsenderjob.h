/*
  This file is part of KAddressBook.

  SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>
  based on code from SPDX-FileCopyrightText: 2014 Clément Vannier <clement.vannier@free.fr>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Item>
#include <QObject>
#include <QStringList>

class KJob;
namespace KABMailSender
{
class MailSenderJob : public QObject
{
    Q_OBJECT

public:
    explicit MailSenderJob(const Akonadi::Item::List &listItem, QObject *parent = nullptr);
    ~MailSenderJob() override;

    void start();

Q_SIGNALS:
    void sendMails(const QStringList &emails);
    void sendMailsError(const QString &error);

private:
    void slotFetchJobFinished(KJob *job);
    void finishJob();
    void fetchItem(const Akonadi::Item &item);
    void fetchNextItem();
    const Akonadi::Item::List mListItem;
    Akonadi::Item::List mItemToFetch;
    QStringList mEmailAddresses;
    int mFetchJobCount = 0;
};
}
