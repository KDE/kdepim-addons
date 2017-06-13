/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef TEMPLATEPARSEREMAILADDRESSREQUESTERAKONADI_H
#define TEMPLATEPARSEREMAILADDRESSREQUESTERAKONADI_H

#include <TemplateParser/TemplateParserEmailAddressRequesterBase>
#include <QVariant>
namespace Akonadi {
class EmailAddressRequester;
}

class TemplateParserEmailAddressRequesterAkonadi : public TemplateParser::TemplateParserEmailAddressRequesterBase
{
    Q_OBJECT
public:
    explicit TemplateParserEmailAddressRequesterAkonadi(QWidget *parent = nullptr, const QList<QVariant> & = {});
    ~TemplateParserEmailAddressRequesterAkonadi();

    QString text() const override;
    void setText(const QString &str) override;
    void clear() override;

private:
    Akonadi::EmailAddressRequester *mEmailAddressRequester;

};

#endif // TEMPLATEPARSEREMAILADDRESSREQUESTERAKONADI_H
