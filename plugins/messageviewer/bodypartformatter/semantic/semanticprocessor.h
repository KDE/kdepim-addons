/*
   Copyright (c) 2017 Volker Krause <vkrause@kde.org>

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

#ifndef SEMANTICPROCESSOR_H
#define SEMANTICPROCESSOR_H

#include "extractorrepository.h"

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/BodyPartFormatter>
#include <MimeTreeParser/MessagePart>

#include <memory>

/** Processor plugin for MimeTreeParser. */
class SemanticProcessor : public MimeTreeParser::Interface::BodyPartFormatter
{
public:
    SemanticProcessor();
    ~SemanticProcessor();

    MimeTreeParser::MessagePart::Ptr process(MimeTreeParser::Interface::BodyPart &part) const override;

private:
    std::shared_ptr<ExtractorRepository> m_repository;
    static std::weak_ptr<ExtractorRepository> s_repository;
};

#endif // SEMANTICPROCESSOR_H
