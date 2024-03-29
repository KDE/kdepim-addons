/*
   SPDX-FileCopyrightText: 2017 Volker Krause <vkrause@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/BodyPartFormatter>
#include <MimeTreeParser/MessagePart>

#include <memory>

/** Processor plugin for MimeTreeParser. */
class ItineraryProcessor : public MimeTreeParser::Interface::BodyPartFormatter
{
public:
    ItineraryProcessor();
    ~ItineraryProcessor() override;

    MimeTreeParser::MessagePart::Ptr process(MimeTreeParser::Interface::BodyPart &part) const override;
};
