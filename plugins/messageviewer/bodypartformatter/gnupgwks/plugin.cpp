/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "plugin.h"

#include "gnupgwksformatter.h"
#include "gnupgwksurlhandler.h"
#include "pgpkeyformatter.h"
#include "pgpkeyurlhandler.h"

namespace
{
enum Index {
    application_pgp_keys,
    application_vnd_gnupg_keys,
    multipart_mixed,
};
}

std::unique_ptr<const MimeTreeParser::Interface::BodyPartFormatter> ApplicationGnuPGWKSPlugin::bodyPartFormatter(int idx) const
{
    switch (idx) {
    case multipart_mixed:
    case application_vnd_gnupg_keys:
        return std::make_unique<ApplicationGnuPGWKSFormatter>();
    case application_pgp_keys:
        return std::make_unique<ApplicationPGPKeyFormatter>();
    default:
        return nullptr;
    }
}

std::unique_ptr<MessageViewer::MessagePartRendererBase> ApplicationGnuPGWKSPlugin::renderer(int idx)
{
    switch (idx) {
    case multipart_mixed:
    case application_vnd_gnupg_keys:
        return std::make_unique<ApplicationGnuPGWKSFormatter>();
    case application_pgp_keys:
        return std::make_unique<ApplicationPGPKeyFormatter>();
    default:
        return nullptr;
    }
}

const MessageViewer::Interface::BodyPartURLHandler *ApplicationGnuPGWKSPlugin::urlHandler(int idx) const
{
    switch (idx) {
    case multipart_mixed:
    case application_vnd_gnupg_keys:
        return new ApplicationGnuPGWKSUrlHandler();
    case application_pgp_keys:
        return new ApplicationPgpKeyUrlHandler();
    default:
        return nullptr;
    }
}

#include "moc_plugin.cpp"
