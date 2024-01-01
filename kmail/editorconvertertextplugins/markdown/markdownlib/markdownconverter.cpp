/*
   SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownconverter.h"
#include "config-markdownplugin.h"
#ifdef DISCOUNT_HAS_HIGHLIGHTING_SUPPORT
#include "markdownhighlighter.h"

#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/Repository>
#include <KSyntaxHighlighting/Theme>
#include <QGuiApplication>
#include <QPalette>
#include <QTextStream>
#endif

#include <KLocalizedString>
extern "C" {
#include <mkdio.h>
}

#ifdef DISCOUNT_HAS_HIGHLIGHTING_SUPPORT
char *external_codefmt(const char *src, int, void *)
{
    KSyntaxHighlighting::Repository repo;
    QString result;
    QTextStream stream(&result);
    MarkdownHighlighter highLighter(&stream);
    highLighter.setDefinition(repo.definitionForName(QStringLiteral("SystemC")));
    highLighter.setTheme(QGuiApplication::palette().color(QPalette::Base).lightness() < 128 ? repo.defaultTheme(KSyntaxHighlighting::Repository::DarkTheme)
                                                                                            : repo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
    highLighter.highlight(QString::fromLatin1(src));
    QByteArray ba = result.toLatin1();
    return qstrdup(ba.data());
}

#endif

MarkdownConverter::MarkdownConverter(QObject *parent)
    : QObject(parent)
{
}

MarkdownConverter::~MarkdownConverter() = default;

QString MarkdownConverter::convertTextToMarkdown(const QString &str)
{
    if (str.isEmpty()) {
        return {};
    }
    const QByteArray textArray = str.toUtf8();
#if defined(MKD_NOLINKS)
    // on discount 2 MKD_NOLINKS is a define
    MMIOT *markdownHandle = mkd_string(textArray.constData(), textArray.size(), 0);
    mkd_flag_t flags = MKD_FENCEDCODE | MKD_GITHUBTAGS | MKD_AUTOLINK;
    if (mEnableEmbeddedLabel) {
        flags |= MKD_LATEX;
    }
    if (mEnableExtraDefinitionLists) {
        flags |= MKD_DLEXTRA;
    }
#if DISCOUNT_HAS_HIGHLIGHTING_SUPPORT
    mkd_e_code_format(markdownHandle, external_codefmt);
#endif
    if (!mkd_compile(markdownHandle, flags)) {
        Q_EMIT failed(i18n("Failed to compile the Markdown document."));
        mkd_cleanup(markdownHandle);
        return {};
    }
#else
    // on discount 2 MKD_NOLINKS is a define

    MMIOT *markdownHandle = mkd_string(textArray.constData(), textArray.size(), nullptr);
    mkd_flag_t *flags = mkd_flags();
    mkd_set_flag_bitmap(flags, MKD_FENCEDCODE | MKD_GITHUBTAGS | MKD_AUTOLINK);
    if (mEnableEmbeddedLabel) {
        mkd_set_flag_num(flags, MKD_LATEX);
    }
    if (mEnableExtraDefinitionLists) {
        mkd_set_flag_num(flags, MKD_DLEXTRA);
    }
#if DISCOUNT_HAS_HIGHLIGHTING_SUPPORT
    mkd_e_code_format(markdownHandle, external_codefmt);
#endif
    if (!mkd_compile(markdownHandle, flags)) {
        Q_EMIT failed(i18n("Failed to compile the Markdown document."));
        mkd_cleanup(markdownHandle);
        mkd_free_flags(flags);
        return {};
    }
    mkd_free_flags(flags);
#endif
    char *htmlDocument;
    const int size = mkd_document(markdownHandle, &htmlDocument);

    const QString html = QString::fromUtf8(htmlDocument, size);
#if 0 // CSS ?
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

#include "moc_markdownconverter.cpp"
