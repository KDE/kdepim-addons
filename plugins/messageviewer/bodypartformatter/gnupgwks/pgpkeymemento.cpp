/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "pgpkeymemento.h"

#include <QGpgME/KeyListJob>
#include <QGpgME/Protocol>
#include <gpgme++/keylistresult.h>
#include <gpgme.h>

PgpKeyMemento::PgpKeyMemento()
    : QObject(nullptr)
    , MimeTreeParser::Interface::BodyPartMemento()
{
}

PgpKeyMemento::~PgpKeyMemento() = default;

void PgpKeyMemento::detach()
{
    disconnect(this, SIGNAL(update(MimeTreeParser::UpdateMode)), nullptr, nullptr);
}

void PgpKeyMemento::notify()
{
    Q_EMIT update(MimeTreeParser::Force);
}

bool PgpKeyMemento::isRunning() const
{
    return mIsRunning;
}

void PgpKeyMemento::setRunning(bool running)
{
    mIsRunning = running;
}

GpgME::Key PgpKeyMemento::key() const
{
    return mKey;
}

QString PgpKeyMemento::error() const
{
    return mError;
}

bool PgpKeyMemento::start(const QString &fingerprint)
{
    auto job = QGpgME::openpgp()->keyListJob(false, false, true);
    connect(job, &QGpgME::KeyListJob::nextKey, this, &PgpKeyMemento::onKeyReceived);
    connect(job, &QGpgME::KeyListJob::result, this, &PgpKeyMemento::onListJobFinished);
    job->start({fingerprint});

    setRunning(true);
    return true;
}

void PgpKeyMemento::exec(const QString &fingerprint)
{
    auto job = QGpgME::openpgp()->keyListJob(false, false, true);
    std::vector<GpgME::Key> outKeys;
    auto result = job->exec({fingerprint}, false, outKeys);
    if (result.error()) {
#if GPGME_VERSION_NUMBER >= 0x011800 // 1.24.0
        mError = QString::fromStdString(result.error().asStdString());
#else
        mError = QString::fromStdString(result.error().asString());
#endif
    } else if (!outKeys.empty()) {
        mKey = outKeys[0];
    }
}

void PgpKeyMemento::onKeyReceived(const GpgME::Key &key)
{
    mKey = key;
}

void PgpKeyMemento::onListJobFinished(const GpgME::KeyListResult &result)
{
    if (result.error()) {
#if GPGME_VERSION_NUMBER >= 0x011800 // 1.24.0
        mError = QString::fromStdString(result.error().asStdString());
#else
        mError = QString::fromStdString(result.error().asString());
#endif
    }

    setRunning(false);
    notify();
}

#include "moc_pgpkeymemento.cpp"
