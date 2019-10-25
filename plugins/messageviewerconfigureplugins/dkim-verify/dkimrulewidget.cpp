/*
   Copyright (C) 2019 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/


#include "dkimrulewidget.h"
#include <KLocalizedString>
#include <QCheckBox>
#include <QFormLayout>
#include <QLineEdit>

DKIMRuleWidget::DKIMRuleWidget(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout *layout = new QFormLayout(this);
    layout->setObjectName(QStringLiteral("layout"));
    layout->setContentsMargins(0, 0, 0, 0);

    mEnabled = new QCheckBox(i18n("Enabled"), this);
    mEnabled->setObjectName(QStringLiteral("enabled"));
    layout->addWidget(mEnabled);

    mDomain = new QLineEdit(this);
    mDomain->setObjectName(QStringLiteral("domain"));
    layout->addRow(i18n("Domain:"), mDomain);

    mSignatureDomainIdentifier = new QLineEdit(this);
    mSignatureDomainIdentifier->setObjectName(QStringLiteral("signaturedomainidentifier"));
    layout->addRow(i18n("SDID:"), mSignatureDomainIdentifier);

    mFrom = new QLineEdit(this);
    mFrom->setObjectName(QStringLiteral("from"));
    layout->addRow(i18n("From:"), mFrom);
}

DKIMRuleWidget::~DKIMRuleWidget()
{

}

void DKIMRuleWidget::loadRule(const MessageViewer::DKIMRule &rule)
{
    mEnabled->setChecked(rule.enabled());
    mDomain->setText(rule.domain());
    mSignatureDomainIdentifier->setText(rule.signedDomainIdentifier().join(QLatin1Char(' ')));
    mFrom->setText(rule.from());
}

MessageViewer::DKIMRule DKIMRuleWidget::rule() const
{
    MessageViewer::DKIMRule rule;
    rule.setEnabled(mEnabled->isChecked());
    rule.setDomain(mDomain->text());
    rule.setSignedDomainIdentifier(mSignatureDomainIdentifier->text().split(QLatin1Char(' ')));
    rule.setFrom(mFrom->text());
    return rule;
}

