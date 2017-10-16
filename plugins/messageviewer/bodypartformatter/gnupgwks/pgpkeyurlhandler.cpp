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

#include "pgpkeyurlhandler.h"

#include <QString>
#include <QUrlQuery>

#include <KLocalizedString>

#include <MimeTreeParser/NodeHelper>
#include <MimeTreeParser/BodyPart>
#include <MessageViewer/Viewer>

#include <QGpgME/Protocol>
#include <QGpgME/ImportJob>
#include <gpgme++/importresult.h>
#include <gpgme++/error.h>

#include <KMessageBox>

using namespace MimeTreeParser::Interface;

QUrlQuery ApplicationPgpKeyUrlHandler::decodePath(const QString &path) const
{
    if (!path.startsWith(QLatin1String("pgpkey?"))) {
        return QUrlQuery();
    }

    return QUrlQuery(path.mid(sizeof("pgpkey?") - 1));
}

bool ApplicationPgpKeyUrlHandler::handleContextMenuRequest(BodyPart *, const QString &, const QPoint &) const
{
    return false;
}

QString ApplicationPgpKeyUrlHandler::statusBarMessage(BodyPart *part, const QString &path) const
{
    Q_UNUSED(part);
    const QUrlQuery q = decodePath(path);
    if (q.queryItemValue(QStringLiteral("action")) == QLatin1String("import")) {
        return i18n("Import the key");
    }

    return QString();
}

bool ApplicationPgpKeyUrlHandler::handleClick(MessageViewer::Viewer *v, BodyPart *part, const QString &path) const
{
    const QUrlQuery q = decodePath(path);
    if (q.queryItemValue(QStringLiteral("action")) == QLatin1String("import")) {
        auto job = QGpgME::openpgp()->importJob();
        auto res = job->exec(part->content()->decodedContent());
        if (res.error()) {
            KMessageBox::detailedError(v,
                                       i18n("An error occurred while importing the key."),
                                       QString::fromUtf8(res.error().asString()),
                                       i18n("Import error"));
        } else {
            KMessageBox::information(v,
                                     i18n("The key has been successfully imported."),
                                     i18n("Import finished"));
        }

        return true;
    }

    return false;
}
