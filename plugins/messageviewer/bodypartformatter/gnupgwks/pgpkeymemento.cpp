/*
  Copyright (c) 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   This library is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published by
   the Free Software Foundation; either version 2 of the License, or (at your
   option) any later version.

   This library is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
   License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to the
   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.
*/

#include "pgpkeymemento.h"

#include <QGpgME/Protocol>
#include <QGpgME/KeyListJob>
#include <gpgme++/keylistresult.h>

PgpKeyMemento::PgpKeyMemento()
    : QObject(nullptr)
    , MimeTreeParser::Interface::BodyPartMemento()
{
}

PgpKeyMemento::~PgpKeyMemento()
{
}

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
    connect(job, &QGpgME::KeyListJob::nextKey,
            this, &PgpKeyMemento::onKeyReceived);
    connect(job, &QGpgME::KeyListJob::result,
            this, &PgpKeyMemento::onListJobFinished);
    job->start({ fingerprint });

    setRunning(true);
    return true;
}

void PgpKeyMemento::exec(const QString &fingerprint)
{
    auto job = QGpgME::openpgp()->keyListJob(false, false, true);
    std::vector<GpgME::Key> outKeys;
    auto result = job->exec({ fingerprint }, false, outKeys);
    if (result.error()) {
        mError = QString::fromStdString(result.error().asString());
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
        mError = QString::fromStdString(result.error().asString());
    }

    setRunning(false);
    notify();
}
