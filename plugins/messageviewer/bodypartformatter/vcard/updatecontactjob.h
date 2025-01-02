/*
   SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KJob>

#include <KContacts/Addressee>

class UpdateContactJob : public KJob
{
    Q_OBJECT
public:
    explicit UpdateContactJob(const QString &email, const KContacts::Addressee &contact, QWidget *parentWidget, QObject *parent = nullptr);
    ~UpdateContactJob() override;

    void start() override;

private:
    void slotSearchDone(KJob *);
    void slotUpdateContactDone(KJob *);

    const QString mEmail;
    const KContacts::Addressee mContact;
    QWidget *const mParentWidget;
};
