/*
   Copyright (C) 2020 Laurent Montel <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "markdowndiscount.h"
#include <QDebug>
extern "C" {
#include <mkdio.h>
}

MarkdownDiscount::MarkdownDiscount()
{

}

MarkdownDiscount::~MarkdownDiscount()
{

}

QString MarkdownDiscount::toHtml() const
{
    if (mText.isEmpty()) {
        return {};
    }
    const QByteArray textArray = mText.toUtf8();
    MMIOT *markdownHandle = mkd_string(textArray.constData(), textArray.count(), 0);
    mkd_flag_t flags = MKD_FENCEDCODE | MKD_GITHUBTAGS | MKD_AUTOLINK;
    if (!mkd_compile(markdownHandle, flags)) {
        qWarning() << "Failed to compile the Markdown document.";
        mkd_cleanup(markdownHandle);
        return {};
    }

    char *htmlDocument;
    const int size = mkd_document(markdownHandle, &htmlDocument);

    const QString html = QString::fromUtf8(htmlDocument, size);
    mkd_cleanup(markdownHandle);
    return html;
}
