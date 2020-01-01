/*
    Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

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

#include "markdowncreatelinkwidget.h"
#include <KLocalizedString>
#include <QFormLayout>
#include <QLineEdit>

MarkdownCreateLinkWidget::MarkdownCreateLinkWidget(QWidget *parent)
    : QWidget(parent)
{
    QFormLayout *mainLayout = new QFormLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mTitle = new QLineEdit(this);
    mTitle->setObjectName(QStringLiteral("title"));
    mTitle->setClearButtonEnabled(true);
    mLink = new QLineEdit(this);
    mLink->setObjectName(QStringLiteral("link"));
    mLink->setClearButtonEnabled(true);

    connect(mTitle, &QLineEdit::textChanged, this, &MarkdownCreateLinkWidget::slotEnableButton);
    connect(mLink, &QLineEdit::textChanged, this, &MarkdownCreateLinkWidget::slotEnableButton);

    mainLayout->addRow(i18n("Title:"), mTitle);
    mainLayout->addRow(i18n("Link:"), mLink);
}

MarkdownCreateLinkWidget::~MarkdownCreateLinkWidget()
{
}

void MarkdownCreateLinkWidget::slotEnableButton()
{
    Q_EMIT enabledOkButton(!mTitle->text().trimmed().isEmpty() && !mLink->text().trimmed().isEmpty());
}

QString MarkdownCreateLinkWidget::linkStr() const
{
    if (mTitle->text().trimmed().isEmpty() && mLink->text().trimmed().isEmpty()) {
        return {};
    }
    return QStringLiteral("[%1](%2)").arg(mTitle->text().trimmed(), mLink->text().trimmed());
}
