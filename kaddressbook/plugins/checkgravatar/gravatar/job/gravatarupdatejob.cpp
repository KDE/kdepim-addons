/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "gravatarupdatejob.h"
#include "kaddressbook_checkgravatarplugin_debug.h"

#include <Gravatar/GravatarResolvUrlJob>

#include <Akonadi/ItemModifyJob>
#include <KContacts/Addressee>
using namespace KABGravatar;

GravatarUpdateJob::GravatarUpdateJob(QObject *parent)
    : QObject(parent)
{
}

GravatarUpdateJob::~GravatarUpdateJob() = default;

void GravatarUpdateJob::start()
{
    if (canStart()) {
        auto job = new Gravatar::GravatarResolvUrlJob(this);
        job->setEmail(mEmail);
        if (job->canStart()) {
            connect(job, &Gravatar::GravatarResolvUrlJob::finished, this, &GravatarUpdateJob::slotGravatarResolvUrlFinished);
            connect(job, &Gravatar::GravatarResolvUrlJob::resolvUrl, this, &GravatarUpdateJob::resolvedUrl);
            job->start();
        } else {
            deleteLater();
        }
    } else {
        deleteLater();
    }
}

bool GravatarUpdateJob::canStart() const
{
    return !mEmail.trimmed().isEmpty() && (mEmail.contains(QLatin1Char('@')));
}

QString GravatarUpdateJob::email() const
{
    return mEmail;
}

void GravatarUpdateJob::setEmail(const QString &email)
{
    mEmail = email;
}

Akonadi::Item GravatarUpdateJob::item() const
{
    return mItem;
}

void GravatarUpdateJob::setItem(const Akonadi::Item &item)
{
    mItem = item;
}

void GravatarUpdateJob::slotGravatarResolvUrlFinished(Gravatar::GravatarResolvUrlJob *job)
{
    if (job) {
        const QPixmap pix = job->pixmap();
        Q_EMIT gravatarPixmap(pix);
        if (mItem.isValid()) {
            updatePixmap(pix);
            return;
        }
    }
    deleteLater();
}

void GravatarUpdateJob::updatePixmap(const QPixmap &pix)
{
    if (mItem.hasPayload<KContacts::Addressee>()) {
        auto contact = mItem.payload<KContacts::Addressee>();
        KContacts::Picture pic = contact.photo();
        pic.setData(pix.toImage());
        contact.setPhoto(pic);
        mItem.setPayload<KContacts::Addressee>(contact);

        // save the new item in akonadi storage
        auto modifyJob = new Akonadi::ItemModifyJob(mItem);
        connect(modifyJob, &KJob::result, this, &GravatarUpdateJob::slotUpdateGravatarDone);
    } else {
        deleteLater();
    }
}

void GravatarUpdateJob::slotUpdateGravatarDone(KJob *job)
{
    if (job->error()) {
        qCDebug(KADDRESSBOOK_CHECKGRAVATAR_LOG) << "Error during modify item :" << job->errorString();
    }
    deleteLater();
}
