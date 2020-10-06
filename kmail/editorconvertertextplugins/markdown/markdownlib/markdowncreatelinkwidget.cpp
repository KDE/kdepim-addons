/*
    SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
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
    mainLayout->setContentsMargins({});

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
