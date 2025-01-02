/*
   SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdowndiscount.h"
#include <QDebug>
extern "C" {
#include <mkdio.h>
}

MarkdownDiscount::MarkdownDiscount() = default;

MarkdownDiscount::~MarkdownDiscount() = default;

QString MarkdownDiscount::toHtml() const
{
    if (mText.isEmpty()) {
        return {};
    }
    const QByteArray textArray = mText.toUtf8();
#if defined(MKD_NOLINKS)
    // on discount 2 MKD_NOLINKS is a define
    MMIOT *markdownHandle = mkd_string(textArray.constData(), textArray.size(), 0);
    mkd_flag_t flags = MKD_FENCEDCODE | MKD_GITHUBTAGS | MKD_AUTOLINK;
    if (!mkd_compile(markdownHandle, flags)) {
        qWarning() << "Failed to compile the Markdown document.";
        mkd_cleanup(markdownHandle);
        return {};
    }
#else
    // on discount 3 MKD_NOLINKS is an enum value
    MMIOT *markdownHandle = mkd_string(textArray.constData(), textArray.size(), nullptr);
    mkd_flag_t *flags = mkd_flags();
    mkd_set_flag_bitmap(flags, MKD_FENCEDCODE | MKD_GITHUBTAGS | MKD_AUTOLINK | MKD_TOC | MKD_IDANCHOR);
    if (!mkd_compile(markdownHandle, flags)) {
        qWarning() << "Failed to compile the Markdown document.";
        mkd_cleanup(markdownHandle);
        mkd_free_flags(flags);
        return {};
    }
    mkd_free_flags(flags);
#endif

    char *htmlDocument;
    const int size = mkd_document(markdownHandle, &htmlDocument);

    const QString html = QString::fromUtf8(htmlDocument, size);
    mkd_cleanup(markdownHandle);
    return html;
}
