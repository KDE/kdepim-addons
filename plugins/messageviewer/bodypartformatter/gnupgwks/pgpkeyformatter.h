/*
  SPDX-FileCopyrightText: 2016 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef PGPKEYFORMATTER_H_
#define PGPKEYFORMATTER_H_

#include <MessageViewer/MessagePartRendererBase>
#include <MimeTreeParser/BodyPartFormatter>

class PgpKeyMessagePart;

class ApplicationPGPKeyFormatter : public MimeTreeParser::Interface::BodyPartFormatter, public MessageViewer::MessagePartRendererBase
{
public:
    ApplicationPGPKeyFormatter() = default;

    MimeTreeParser::MessagePartPtr process(MimeTreeParser::Interface::BodyPart &part) const override;
    bool render(const MimeTreeParser::MessagePartPtr &msgPart, MessageViewer::HtmlWriter *htmlWriter, MessageViewer::RenderContext *context) const override;

private:
    QString render(const PgpKeyMessagePart &mp) const;
};

#endif
