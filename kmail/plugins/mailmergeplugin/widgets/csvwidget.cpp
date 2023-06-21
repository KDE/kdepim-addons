/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "csvwidget.h"

#include <KLocalizedString>
#include <KUrlRequester>
#include <QLabel>
#include <QVBoxLayout>

using namespace MailMerge;

CsvWidget::CsvWidget(QWidget *parent)
    : QWidget(parent)
    , mCvsUrlRequester(new KUrlRequester(this))
{
    auto csvWidgetLayout = new QVBoxLayout(this);
    csvWidgetLayout->setObjectName(QStringLiteral("csvWidgetLayout"));
    csvWidgetLayout->setContentsMargins({});

    auto lab = new QLabel(i18n("Path:"), this);
    lab->setObjectName(QStringLiteral("label"));
    csvWidgetLayout->addWidget(lab);
    mCvsUrlRequester->setObjectName(QStringLiteral("cvsurlrequester"));
    csvWidgetLayout->addWidget(mCvsUrlRequester);
}

CsvWidget::~CsvWidget() = default;

void CsvWidget::setPath(const QUrl &path)
{
    mCvsUrlRequester->setUrl(path);
}

QUrl CsvWidget::path() const
{
    return mCvsUrlRequester->url();
}

#include "moc_csvwidget.cpp"
