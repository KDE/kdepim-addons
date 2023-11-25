/*
  SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "mailmergewidget.h"
#include "../widgets/addressbookwidget.h"
#include "../widgets/csvwidget.h"

#include "attachmentlistwidget.h"

#include <KLocalizedString>
#include <QComboBox>

#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QVBoxLayout>

using namespace MailMerge;

MailMergeWidget::MailMergeWidget(QWidget *parent)
    : QWidget(parent)
    , mSource(new QComboBox(this))
    , mStackedWidget(new QStackedWidget(this))
    , mCsvWidget(new MailMerge::CsvWidget(this))
    , mAddressbookWidget(new MailMerge::AddressBookWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));

    auto hbox = new QHBoxLayout;
    mainLayout->addLayout(hbox);

    auto lab = new QLabel(i18n("Source:"), this);
    lab->setObjectName(QLatin1StringView("lab"));
    hbox->addWidget(lab);

    mSource->setObjectName(QLatin1StringView("source"));
    mSource->addItem(i18n("Address Book"), AddressBook);
    mSource->addItem(i18n("CSV"), CSV);
    connect(mSource, &QComboBox::currentIndexChanged, this, &MailMergeWidget::slotSourceChanged);
    connect(mSource, &QComboBox::activated, this, &MailMergeWidget::slotSourceChanged);

    hbox->addWidget(mSource);

    mStackedWidget->setObjectName(QLatin1StringView("stackedwidget"));
    mainLayout->addWidget(mStackedWidget);

    mAddressbookWidget->setObjectName(QLatin1StringView("addressbookwidget"));
    mStackedWidget->addWidget(mAddressbookWidget);

    mCsvWidget->setObjectName(QLatin1StringView("csvwidget"));

    mStackedWidget->addWidget(mCsvWidget);

    lab = new QLabel(i18n("Attachment:"), this);
    mainLayout->addWidget(lab);

    auto buttonCode = static_cast<PimCommon::SimpleStringListEditor::ButtonCode>(
        PimCommon::SimpleStringListEditor::Add | PimCommon::SimpleStringListEditor::Remove | PimCommon::SimpleStringListEditor::Modify);
    mAttachment = new AttachmentListWidget(this, buttonCode, i18n("A&dd..."), i18n("Re&move"), i18n("Mod&ify..."));
    mAttachment->setObjectName(QLatin1StringView("attachment-list"));

    mainLayout->addWidget(mAttachment);
    mainLayout->addStretch();
}

MailMergeWidget::~MailMergeWidget() = default;

void MailMergeWidget::slotSourceChanged(int index)
{
    if (index != -1) {
        Q_EMIT sourceModeChanged(static_cast<SourceType>(mSource->itemData(index).toInt()));
        mStackedWidget->setCurrentIndex(index);
    }
}

#include "moc_mailmergewidget.cpp"
