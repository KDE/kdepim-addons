/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

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
{
    QVBoxLayout *vbox = new QVBoxLayout(this);

    QHBoxLayout *hbox = new QHBoxLayout;
    vbox->addLayout(hbox);

    QLabel *lab = new QLabel(i18n("Source:"), this);
    hbox->addWidget(lab);

    mSource = new QComboBox(this);
    mSource->setObjectName(QStringLiteral("source"));
    mSource->addItem(i18n("Address Book"), AddressBook);
    mSource->addItem(i18n("CSV"), CSV);
    connect(mSource, qOverload<int>(&QComboBox::currentIndexChanged), this, &MailMergeWidget::slotSourceChanged);
    connect(mSource, qOverload<int>(&QComboBox::activated), this, &MailMergeWidget::slotSourceChanged);

    hbox->addWidget(mSource);

    mStackedWidget = new QStackedWidget(this);
    mStackedWidget->setObjectName(QStringLiteral("stackedwidget"));
    vbox->addWidget(mStackedWidget);

    mAddressbookWidget = new MailMerge::AddressBookWidget(this);
    mAddressbookWidget->setObjectName(QStringLiteral("addressbookwidget"));
    mStackedWidget->addWidget(mAddressbookWidget);

    mCsvWidget = new MailMerge::CsvWidget(this);
    mCsvWidget->setObjectName(QStringLiteral("csvwidget"));

    mStackedWidget->addWidget(mCsvWidget);

    lab = new QLabel(i18n("Attachment:"), this);
    vbox->addWidget(lab);

    PimCommon::SimpleStringListEditor::ButtonCode buttonCode = static_cast<PimCommon::SimpleStringListEditor::ButtonCode>(
        PimCommon::SimpleStringListEditor::Add | PimCommon::SimpleStringListEditor::Remove | PimCommon::SimpleStringListEditor::Modify);
    mAttachment = new AttachmentListWidget(this, buttonCode, i18n("A&dd..."), i18n("Re&move"), i18n("Mod&ify..."));
    mAttachment->setObjectName(QStringLiteral("attachment-list"));

    vbox->addWidget(mAttachment);
    vbox->addStretch();
}

MailMergeWidget::~MailMergeWidget()
{
}

void MailMergeWidget::slotSourceChanged(int index)
{
    if (index != -1) {
        Q_EMIT sourceModeChanged(static_cast<SourceType>(mSource->itemData(index).toInt()));
        mStackedWidget->setCurrentIndex(index);
    }
}
