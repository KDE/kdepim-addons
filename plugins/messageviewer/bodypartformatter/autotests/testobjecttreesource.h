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

#ifndef TESTOBJECTTREESOURCE_H
#define TESTOBJECTTREESOURCE_H

#include <MessageViewer/ObjectTreeEmptySource>
#include <MessageViewer/CSSHelperBase>
#include <MessageViewer/AttachmentStrategy>

class TestObjectTreeSource : public MessageViewer::EmptySource
{
public:
    TestObjectTreeSource(MessageViewer::HtmlWriter *writer, MessageViewer::CSSHelperBase *cssHelper)
        : mWriter(writer)
        , mCSSHelper(cssHelper)
        , mHtmlLoadExternal(false)
        , mShowSignatureDetails(false)
    {
    }

    MessageViewer::HtmlWriter *htmlWriter() const override
    {
        return mWriter;
    }

    MessageViewer::CSSHelperBase *cssHelper() const override
    {
        return mCSSHelper;
    }

    bool htmlLoadExternal() const override
    {
        return mHtmlLoadExternal;
    }

    void setHtmlLoadExternal(bool loadExternal)
    {
        mHtmlLoadExternal = loadExternal;
    }

    bool decryptMessage() const override
    {
        return false;
    }

    bool showSignatureDetails() const override
    {
        return mShowSignatureDetails;
    }

    void setShowSignatureDetails(bool showSignatureDetails)
    {
        mShowSignatureDetails = showSignatureDetails;
    }

    void setHtmlMode(MimeTreeParser::Util::HtmlMode mode, const QList<MimeTreeParser::Util::HtmlMode> &availableModes) override
    {
        Q_UNUSED(mode)
        Q_UNUSED(availableModes)
    }

    int levelQuote() const override
    {
        return false;
    }

    const QTextCodec *overrideCodec() override
    {
        return nullptr;
    }

    QString createMessageHeader(KMime::Message *message) override
    {
        Q_UNUSED(message);
        return QString();
    }

    const MessageViewer::AttachmentStrategy *attachmentStrategy() const override
    {
        return MessageViewer::AttachmentStrategy::smart();
    }

    bool autoImportKeys() const override
    {
        return false;
    }

    bool showEmoticons() const override
    {
        return false;
    }

    bool showExpandQuotesMark() const override
    {
        return false;
    }

    MimeTreeParser::Util::HtmlMode preferredMode() const override
    {
        return MimeTreeParser::Util::Html;
    }

private:
    MessageViewer::HtmlWriter *mWriter = nullptr;
    MessageViewer::CSSHelperBase *mCSSHelper = nullptr;
    bool mHtmlLoadExternal;
    bool mShowSignatureDetails;
};

#endif
