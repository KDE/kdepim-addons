/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "pgpkeyurlhandler.h"

#include <QString>
#include <QUrlQuery>

#include <KLocalizedString>

#include <MessageViewer/Viewer>
#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/NodeHelper>

#include <QGpgME/ImportJob>
#include <QGpgME/Protocol>
#include <gpgme++/error.h>
#include <gpgme++/importresult.h>

#include <KMessageBox>

using namespace MimeTreeParser::Interface;

QUrlQuery ApplicationPgpKeyUrlHandler::decodePath(const QString &path) const
{
    if (!path.startsWith(QLatin1StringView("pgpkey?"))) {
        return {};
    }

    return QUrlQuery(path.mid(sizeof("pgpkey?") - 1));
}

bool ApplicationPgpKeyUrlHandler::handleContextMenuRequest(BodyPart *, const QString &, const QPoint &) const
{
    return false;
}

QString ApplicationPgpKeyUrlHandler::statusBarMessage(BodyPart *part, const QString &path) const
{
    Q_UNUSED(part)
    const QUrlQuery q = decodePath(path);
    if (q.queryItemValue(QStringLiteral("action")) == QLatin1StringView("import")) {
        return i18n("Import the key");
    }

    return {};
}

QString ApplicationPgpKeyUrlHandler::name() const
{
    return QStringLiteral("ApplicationPgpKeyUrlHandler");
}

bool ApplicationPgpKeyUrlHandler::handleClick(MessageViewer::Viewer *v, BodyPart *part, const QString &path) const
{
    const QUrlQuery q = decodePath(path);
    if (q.queryItemValue(QStringLiteral("action")) == QLatin1StringView("import")) {
        auto job = QGpgME::openpgp()->importJob();
        auto res = job->exec(part->content()->decodedContent());
        if (res.error()) {
            KMessageBox::detailedError(v,
                                       i18n("An error occurred while importing the key."),
                                       QString::fromUtf8(res.error().asString()),
                                       i18nc("@title:window", "Import error"));
        } else if (res.numConsidered() == 0) {
            KMessageBox::error(v, i18n("No keys to import where found."), i18nc("@title:window", "Import error"));
        } else {
            KMessageBox::information(v, i18n("The key has been successfully imported."), i18nc("@title:window", "Import finished"));
        }

        return true;
    }

    return false;
}
