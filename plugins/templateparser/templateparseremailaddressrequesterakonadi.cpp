/*
   Copyright (C) 2017-2018 Montel Laurent <montel@kde.org>

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

#include "templateparseremailaddressrequesterakonadi.h"
#include <QHBoxLayout>
#include <Akonadi/Contact/EmailAddressRequester>
#include <kpluginfactory.h>

K_PLUGIN_CLASS_WITH_JSON(TemplateParserEmailAddressRequesterAkonadi,
                         "templateparseremailaddressrequesterakonadi.json")

TemplateParserEmailAddressRequesterAkonadi::TemplateParserEmailAddressRequesterAkonadi(QWidget *parent, const QList<QVariant> &)
    : TemplateParser::TemplateParserEmailAddressRequesterBase(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setMargin(0);
    mEmailAddressRequester = new Akonadi::EmailAddressRequester(this);
    mEmailAddressRequester->setObjectName(QStringLiteral("EmailAddressRequester"));
    mainLayout->addWidget(mEmailAddressRequester);
    connect(mEmailAddressRequester, &Akonadi::EmailAddressRequester::textChanged, this, &TemplateParser::TemplateParserEmailAddressRequesterBase::textChanged);
}

TemplateParserEmailAddressRequesterAkonadi::~TemplateParserEmailAddressRequesterAkonadi()
{
    disconnect(mEmailAddressRequester, &Akonadi::EmailAddressRequester::textChanged, this, &TemplateParser::TemplateParserEmailAddressRequesterBase::textChanged);
}

QString TemplateParserEmailAddressRequesterAkonadi::text() const
{
    return mEmailAddressRequester->text();
}

void TemplateParserEmailAddressRequesterAkonadi::setText(const QString &str)
{
    mEmailAddressRequester->setText(str);
}

void TemplateParserEmailAddressRequesterAkonadi::clear()
{
    mEmailAddressRequester->clear();
}

#include "templateparseremailaddressrequesterakonadi.moc"
