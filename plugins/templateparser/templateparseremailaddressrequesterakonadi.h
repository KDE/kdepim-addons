/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QVariant>
#include <TemplateParser/TemplateParserEmailAddressRequesterBase>
namespace Akonadi
{
class EmailAddressRequester;
}

class TemplateParserEmailAddressRequesterAkonadi : public TemplateParser::TemplateParserEmailAddressRequesterBase
{
    Q_OBJECT
public:
    explicit TemplateParserEmailAddressRequesterAkonadi(QWidget *parent = nullptr, const QList<QVariant> & = {});
    ~TemplateParserEmailAddressRequesterAkonadi() override;

    [[nodiscard]] QString text() const override;
    void setText(const QString &str) override;
    void clear() override;

private:
    Akonadi::EmailAddressRequester *const mEmailAddressRequester;
};
