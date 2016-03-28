/*
  Copyright (C) 2010 Klaralvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Copyright (c) 2010 Leo Franchi <lfranchi@kde.org>

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

#ifndef MESSAGECORE_TESTS_UTIL_H
#define MESSAGECORE_TESTS_UTIL_H

#include <MessageViewer/ObjectTreeEmptySource>
#include <MimeTreeParser/CSSHelperBase>
#include <MimeTreeParser/AttachmentStrategy>

class TestObjectTreeSource : public MessageViewer::EmptySource
{
public:
    TestObjectTreeSource(MimeTreeParser::HtmlWriter *writer,
                         MimeTreeParser::CSSHelperBase *cssHelper)
        : mWriter(writer)
        , mCSSHelper(cssHelper)
        , mHtmlLoadExternal(false)
        , mHtmlMail(true)
    {
    }

    MimeTreeParser::HtmlWriter *htmlWriter() Q_DECL_OVERRIDE {
        return mWriter;
    }

    MimeTreeParser::CSSHelperBase *cssHelper() Q_DECL_OVERRIDE {
        return mCSSHelper;
    }

    bool htmlLoadExternal() const Q_DECL_OVERRIDE
    {
        return mHtmlLoadExternal;
    }

    void setHtmlLoadExternal(bool loadExternal)
    {
        mHtmlLoadExternal = loadExternal;
    }

    bool htmlMail() const Q_DECL_OVERRIDE
    {
        return mHtmlMail;
    }

    void setHtmlMail(bool htmlMail)
    {
        mHtmlMail = htmlMail;
    }

    bool decryptMessage() const Q_DECL_OVERRIDE
    {
        return false;
    }
    bool showSignatureDetails() const Q_DECL_OVERRIDE
    {
        return false;
    }
    void setHtmlMode(MimeTreeParser::Util::HtmlMode mode) Q_DECL_OVERRIDE {
        Q_UNUSED(mode)
    }
    int levelQuote() const Q_DECL_OVERRIDE
    {
        return false;
    }
    const QTextCodec *overrideCodec() Q_DECL_OVERRIDE {
        return 0;
    }
    QString createMessageHeader(KMime::Message *message) Q_DECL_OVERRIDE {
        Q_UNUSED(message);
        return QString();
    }
    const MimeTreeParser::AttachmentStrategy *attachmentStrategy() Q_DECL_OVERRIDE {
        return MimeTreeParser::AttachmentStrategy::smart();
    }
    QObject *sourceObject() Q_DECL_OVERRIDE {
        return 0;
    }

    bool autoImportKeys() const Q_DECL_OVERRIDE
    {
        return false;
    }
    bool showEmoticons() const Q_DECL_OVERRIDE
    {
        return false;
    }
    bool showExpandQuotesMark() const Q_DECL_OVERRIDE
    {
        return false;
    }

private:
    MimeTreeParser::HtmlWriter *mWriter;
    MimeTreeParser::CSSHelperBase *mCSSHelper;
    bool mHtmlLoadExternal;
    bool mHtmlMail;
};

#endif
