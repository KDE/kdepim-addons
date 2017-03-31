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

namespace
{
enum Index {
    multipart_mixed,
    application_vnd_gnupg_keys,
    application_pgp_keys
};
}

const char *ApplicationGnuPGWKSPlugin::type(int idx) const
{
    switch (idx) {
    case multipart_mixed:
        return "multipart";
    case application_vnd_gnupg_keys:
    case application_pgp_keys:
        return "application";
    default:
        return nullptr;
    }
}

const char *ApplicationGnuPGWKSPlugin::subtype(int idx) const
{
    switch (idx) {
    case multipart_mixed:
        return "mixed";
    case application_vnd_gnupg_keys:
        return "vnd.gnupg.wks";
    case application_pgp_keys:
        return "pgp-keys";
    default:
        return nullptr;
    }
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

const MimeTreeParser::Interface::BodyPartURLHandler *ApplicationGnuPGWKSPlugin::urlHandler(int idx) const
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

extern "C"
Q_DECL_EXPORT MimeTreeParser::Interface::BodyPartFormatterPlugin *
messageviewer_bodypartformatter_application_gnupgwks_create_bodypart_formatter_plugin()
{
    return new ApplicationGnuPGWKSPlugin();
}
