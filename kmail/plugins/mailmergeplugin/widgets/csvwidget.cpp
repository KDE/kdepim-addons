/*
  SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

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
    csvWidgetLayout->setObjectName(QLatin1StringView("csvWidgetLayout"));
    csvWidgetLayout->setContentsMargins({});

    auto lab = new QLabel(i18nc("@label:textbox", "Path:"), this);
    lab->setObjectName(QLatin1StringView("label"));
    csvWidgetLayout->addWidget(lab);
    mCvsUrlRequester->setObjectName(QLatin1StringView("cvsurlrequester"));
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
