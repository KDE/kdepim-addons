/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/MessagePartRendererBase>
#include <MimeTreeParser/BodyPartFormatter>

class GnuPGWKSMessagePart;
class GnuPGWKSMemento;

class ApplicationGnuPGWKSFormatter : public MimeTreeParser::Interface::BodyPartFormatter, public MessageViewer::MessagePartRendererBase
{
public:
    ApplicationGnuPGWKSFormatter() = default;

    MimeTreeParser::MessagePartPtr process(MimeTreeParser::Interface::BodyPart &part) const override;
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override;

private:
    enum WKSStatus {
        CheckingPublishing,
        NotPublished,
        Published,
    };

    QString render(const GnuPGWKSMessagePart &mp, WKSStatus status) const;
};

