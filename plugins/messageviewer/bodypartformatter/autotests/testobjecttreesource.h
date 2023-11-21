/*
  SPDX-FileCopyrightText: 2010 Klaralvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
  SPDX-FileCopyrightText: 2010 Leo Franchi <lfranchi@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/AttachmentStrategy>
#include <MessageViewer/CSSHelperBase>
#include <MessageViewer/ObjectTreeEmptySource>

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

    QByteArray overrideCodecName() const override
    {
        return {};
    }

    QString createMessageHeader(KMime::Message *message) override
    {
        Q_UNUSED(message)
        return {};
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
