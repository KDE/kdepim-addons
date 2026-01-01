/*
   SPDX-FileCopyrightText: 2012-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "vcardmemento.h"
#include "vcard_debug.h"
#include <Akonadi/ContactSearchJob>
using namespace MessageViewer;

VcardMemento::VcardMemento(const QStringList &emails)
    : QObject(nullptr)
{
    mVCardList.reserve(emails.count());
    for (const QString &str : emails) {
        VCard vcard(str, false);
        mVCardList.append(vcard);
    }
    checkEmail();
}

VcardMemento::~VcardMemento() = default;

void VcardMemento::checkEmail()
{
    auto searchJob = new Akonadi::ContactSearchJob();
    searchJob->setQuery(Akonadi::ContactSearchJob::Email, mVCardList.at(mIndex).email.toLower());
    connect(searchJob, &Akonadi::ContactSearchJob::result, this, &VcardMemento::slotSearchJobFinished);
}

void VcardMemento::slotSearchJobFinished(KJob *job)
{
    auto searchJob = static_cast<Akonadi::ContactSearchJob *>(job);
    if (searchJob->error()) {
        qCWarning(VCARD_LOG) << "Unable to fetch contact:" << searchJob->errorText();
        mIndex++;
        continueToCheckEmail();
        return;
    }

    const int contactSize(searchJob->contacts().size());
    if (contactSize >= 1) {
        VCard vcard = mVCardList.at(mIndex);
        vcard.found = true;
        vcard.address = searchJob->contacts().at(0);
        mVCardList[mIndex] = vcard;
        if (contactSize > 1) {
            qCDebug(VCARD_LOG) << " more than 1 contact was found";
        }
    }

    mIndex++;
    continueToCheckEmail();
}

void VcardMemento::continueToCheckEmail()
{
    if (mIndex == mVCardList.count()) {
        mFinished = true;
        Q_EMIT update(MimeTreeParser::Delayed);
    } else {
        checkEmail();
    }
}

bool VcardMemento::finished() const
{
    return mFinished;
}

void VcardMemento::detach()
{
    disconnect(this, SIGNAL(update(MimeTreeParser::UpdateMode)), nullptr, nullptr);
}

bool VcardMemento::vcardExist(int index) const
{
    // We can have more vcard as we have emails. For example a vcard without email will not created here => necessary to make this check see #405791
    if (index >= mVCardList.count()) {
        return false;
    }
    return mVCardList.at(index).found;
}

KContacts::Addressee VcardMemento::address(int index) const
{
    // We can have more vcard as we have emails. For example a vcard without email will not created here => necessary to make this check see #405791
    if (index >= mVCardList.count()) {
        return {};
    }
    return mVCardList.at(index).address;
}

#include "moc_vcardmemento.cpp"
