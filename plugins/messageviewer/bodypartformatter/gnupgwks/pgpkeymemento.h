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

#ifndef PGPKEYMEMENTO_H_
#define PGPKEYMEMENTO_H_

#include <QObject>
#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/Enums>

#include <gpgme++/key.h>

namespace GpgME {
class KeyListResult;
}

class PgpKeyMemento : public QObject
                    , public MimeTreeParser::Interface::BodyPartMemento
{
    Q_OBJECT
public:
    explicit PgpKeyMemento();
    ~PgpKeyMemento();

    bool isRunning() const;
    void setRunning(bool running);

    GpgME::Key key() const;
    QString error() const;

    bool start(const QString &fingerprint);
    void exec(const QString &fingerprint);

    void detach() Q_DECL_OVERRIDE;

Q_SIGNALS:
    void update(MimeTreeParser::UpdateMode update);

private:
    void notify();

private Q_SLOTS:
    void onKeyReceived(const GpgME::Key &key);
    void onListJobFinished(const GpgME::KeyListResult &result);

private:
    GpgME::Key mKey;
    QString mError;
    bool mIsRunning;
};

#endif
