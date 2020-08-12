/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    explicit TemplateParserEmailAddressRequesterAkonadi(QWidget *parent = nullptr, const QList<QVariant> & =
    {
    });
    ~TemplateParserEmailAddressRequesterAkonadi() override;

    QString text() const override;
    void setText(const QString &str) override;
    void clear() override;

private:
    Akonadi::EmailAddressRequester *mEmailAddressRequester = nullptr;
};

#endif // TEMPLATEPARSEREMAILADDRESSREQUESTERAKONADI_H
