/*
   Copyright (C) 2018 Montel Laurent <montel@kde.org>

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

#include "markdownconverter.h"
extern "C" {
#include <mkdio.h>
}

MarkdownConverter::MarkdownConverter(QObject *parent)
    : QObject(parent)
{

}

MarkdownConverter::~MarkdownConverter()
{

}

QString MarkdownConverter::convertTextToMarkdown(const QString &str)
{
    if (str.isEmpty()) {
        return {};
    }
    const QByteArray textArray = str.toUtf8();

    //TODO verify
    MMIOT *markdownHandle = mkd_string(textArray.constData(), 0, 0);
    char *htmlDocument;
    const int size = mkd_document( markdownHandle, &htmlDocument );

    const QString html = QString::fromUtf8( htmlDocument, size );

    mkd_cleanup( markdownHandle );
    return html;
}
