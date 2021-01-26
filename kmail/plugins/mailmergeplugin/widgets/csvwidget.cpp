/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

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
{
    QVBoxLayout *csvWidgetLayout = new QVBoxLayout;
    csvWidgetLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(csvWidgetLayout);

    QLabel *lab = new QLabel(i18n("Path:"));
    lab->setObjectName(QStringLiteral("label"));
    csvWidgetLayout->addWidget(lab);
    mCvsUrlRequester = new KUrlRequester;
    mCvsUrlRequester->setObjectName(QStringLiteral("cvsurlrequester"));
    csvWidgetLayout->addWidget(mCvsUrlRequester);
}

CsvWidget::~CsvWidget()
{
}

void CsvWidget::setPath(const QUrl &path)
{
    mCvsUrlRequester->setUrl(path);
}

QUrl CsvWidget::path() const
{
    return mCvsUrlRequester->url();
}
