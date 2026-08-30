/*
  SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "csvwidget.h"

#include <KLocalizedString>
#include <KUrlRequester>
#include <QLabel>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

using namespace MailMerge;

CsvWidget::CsvWidget(QWidget *parent)
    : QWidget(parent)
    , mCvsUrlRequester(new KUrlRequester(this))
{
    auto csvWidgetLayout = new QVBoxLayout(this);
    csvWidgetLayout->setObjectName("csvWidgetLayout"_L1);
    csvWidgetLayout->setContentsMargins({});

    auto lab = new QLabel(i18nc("@label:textbox", "Path:"), this);
    lab->setObjectName("label"_L1);
    csvWidgetLayout->addWidget(lab);
    mCvsUrlRequester->setObjectName("cvsurlrequester"_L1);
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
