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

#include "plugin.h"

#include "gnupgwksformatter.h"
#include "gnupgwksurlhandler.h"
#include "pgpkeyformatter.h"
#include "pgpkeyurlhandler.h"

namespace {
enum Index {
    application_pgp_keys,
    application_vnd_gnupg_keys,
    multipart_mixed
};
}

const MimeTreeParser::Interface::BodyPartFormatter *ApplicationGnuPGWKSPlugin::bodyPartFormatter(int idx) const
{
    switch (idx) {
    case multipart_mixed:
    case application_vnd_gnupg_keys:
        return new ApplicationGnuPGWKSFormatter();
    case application_pgp_keys:
        return new ApplicationPGPKeyFormatter();
    default:
        return nullptr;
    }
}

MessageViewer::MessagePartRendererBase* ApplicationGnuPGWKSPlugin::renderer(int idx)
{
    switch (idx) {
    case multipart_mixed:
    case application_vnd_gnupg_keys:
        return new ApplicationGnuPGWKSFormatter();
    case application_pgp_keys:
        return new ApplicationPGPKeyFormatter();
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
