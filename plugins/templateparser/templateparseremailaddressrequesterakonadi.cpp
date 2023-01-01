/*
   SPDX-FileCopyrightText: 2017-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "templateparseremailaddressrequesterakonadi.h"
#include <Akonadi/EmailAddressRequester>
#include <KPluginFactory>
#include <QHBoxLayout>

K_PLUGIN_CLASS_WITH_JSON(TemplateParserEmailAddressRequesterAkonadi, "templateparseremailaddressrequesterakonadi.json")

TemplateParserEmailAddressRequesterAkonadi::TemplateParserEmailAddressRequesterAkonadi(QWidget *parent, const QList<QVariant> &)
    : TemplateParser::TemplateParserEmailAddressRequesterBase(parent)
    , mEmailAddressRequester(new Akonadi::EmailAddressRequester(this))
{
    auto mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});
    mEmailAddressRequester->setObjectName(QStringLiteral("EmailAddressRequester"));
    mainLayout->addWidget(mEmailAddressRequester);
    connect(mEmailAddressRequester, &Akonadi::EmailAddressRequester::textChanged, this, &TemplateParser::TemplateParserEmailAddressRequesterBase::textChanged);
}

TemplateParserEmailAddressRequesterAkonadi::~TemplateParserEmailAddressRequesterAkonadi()
{
    disconnect(mEmailAddressRequester,
               &Akonadi::EmailAddressRequester::textChanged,
               this,
               &TemplateParser::TemplateParserEmailAddressRequesterBase::textChanged);
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
