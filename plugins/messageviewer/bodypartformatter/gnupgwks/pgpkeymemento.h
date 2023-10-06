/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/Enums>
#include <QObject>

#include <gpgme++/key.h>

namespace GpgME
{
class KeyListResult;
}

class PgpKeyMemento : public QObject, public MimeTreeParser::Interface::BodyPartMemento
{
    Q_OBJECT
public:
    PgpKeyMemento();
    ~PgpKeyMemento() override;

    [[nodiscard]] bool isRunning() const;
    void setRunning(bool running);

    [[nodiscard]] GpgME::Key key() const;
    [[nodiscard]] QString error() const;

    [[nodiscard]] bool start(const QString &fingerprint);
    void exec(const QString &fingerprint);

    void detach() override;

Q_SIGNALS:
    void update(MimeTreeParser::UpdateMode update);

private:
    void notify();

private:
    void onKeyReceived(const GpgME::Key &key);
    void onListJobFinished(const GpgME::KeyListResult &result);

    GpgME::Key mKey;
    QString mError;
    bool mIsRunning = false;
};
