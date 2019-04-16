/*
   Copyright (C) 2018-2019 Montel Laurent <montel@kde.org>

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
#include <KLocalizedString>
#include "config-markdownplugin.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern "C" {
#include <mkdio.h>
}

#ifdef DISCOUNT_HAS_HIGHLIGHTING_SUPPORT
char *
external_codefmt(const char *src, int len, void *lang)
{
    std::cout << "src :" << src << std::endl;
    int extra = 0;
    int i, x;
    char *res;

//    if ( lang == nullptr )
//        lang = "generic_code";

    for ( i=0; i < len; i++) {
        if ( src[i] == '&' )
            extra += 5;
        else if ( src[i] == '<' || src[i] == '>' )
            extra += 4;
    }

    /* 80 characters for the format wrappers */
//    if ( (res = malloc(len+extra+80+strlen(lang))) ==0 )
//        /* out of memory?  drat! */
//        return nullptr;

    sprintf(res, "<pre><code class=\"%s\">\n", lang);
    x = strlen(res);
    for ( i=0; i < len; i++ ) {
//        switch (src[i]) {
//        case '&':   strcpy(&src[x], "&amp;");
//                    x += 5 /*strlen(&amp;)*/ ;
//                    break;
//        case '<':   strcpy(&src[x], "&lt;");
//                    x += 4 /*strlen(&lt;)*/ ;
//                    break;
//        case '>':   strcpy(&src[x], "&gt;");
//                    x += 4 /*strlen(&gt;)*/ ;
//                    break;
//        default:
        res[x++] = src[i];
//                    break;
        }
//    }
    strcpy(&res[x], "</code></pre>\n");
    return res;
}
#endif
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

    MMIOT *markdownHandle = mkd_string(textArray.constData(), textArray.count(), 0);
    mkd_flag_t flags = MKD_FENCEDCODE | MKD_GITHUBTAGS | MKD_AUTOLINK;
    if (mEnableEmbeddedLabel) {
        flags |= MKD_LATEX;
    }
    if (mEnableExtraDefinitionLists) {
        flags |= MKD_DLEXTRA;
    }
#ifdef DISCOUNT_HAS_HIGHLIGHTING_SUPPORT
    mkd_e_code_format(markdownHandle, external_codefmt);
#endif
    if (!mkd_compile(markdownHandle, flags)) {
        Q_EMIT failed(i18n("Failed to compile the Markdown document."));
        mkd_cleanup(markdownHandle);
        return {};
    }

    char *htmlDocument;
    const int size = mkd_document(markdownHandle, &htmlDocument);

    const QString html = QString::fromUtf8(htmlDocument, size);
#if 0
    char *cssDocument;
    const int cssSize = mkd_css(markdownHandle, &cssDocument);

    const QString css = QString::fromUtf8(cssDocument, cssSize);
#endif

    mkd_cleanup(markdownHandle);
    return html;
}

bool MarkdownConverter::enableEmbeddedLabel() const
{
    return mEnableEmbeddedLabel;
}

void MarkdownConverter::setEnableEmbeddedLabel(bool enableEmbeddedLabel)
{
    mEnableEmbeddedLabel = enableEmbeddedLabel;
}

bool MarkdownConverter::enableExtraDefinitionLists() const
{
    return mEnableExtraDefinitionLists;
}

void MarkdownConverter::setEnableExtraDefinitionLists(bool enableExtraDefinitionLists)
{
    mEnableExtraDefinitionLists = enableExtraDefinitionLists;
}
