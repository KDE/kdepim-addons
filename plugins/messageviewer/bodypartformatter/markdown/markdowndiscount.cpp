/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

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
    MMIOT *markdownHandle = mkd_string(textArray.constData(), textArray.size(), 0);
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
