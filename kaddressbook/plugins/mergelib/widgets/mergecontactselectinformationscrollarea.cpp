/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactselectinformationscrollarea.h"
#include "job/mergecontactsjob.h"
#include "kaddressbookmergelibprivate_debug.h"
#include "mergecontactselectinformationwidget.h"
#include "widgets/mergecontactinfowidget.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QPushButton>
#include <QScrollArea>
#include <QStackedWidget>
#include <QVBoxLayout>
using namespace KABMergeContacts;

MergeContactSelectInformationScrollArea::MergeContactSelectInformationScrollArea(QWidget *parent)
    : QWidget(parent)
{
    auto vbox = new QVBoxLayout(this);
    vbox->setContentsMargins({});
    mStackWidget = new QStackedWidget;
    mStackWidget->setObjectName(QStringLiteral("stackwidget"));
    vbox->addWidget(mStackWidget);

    auto selectMergeWidget = new QWidget;
    selectMergeWidget->setObjectName(QStringLiteral("selectwidget"));
    auto layout = new QVBoxLayout;
    selectMergeWidget->setLayout(layout);
    auto area = new QScrollArea;
    area->setWidgetResizable(true);
    area->setObjectName(QStringLiteral("scrollarea"));
    layout->addWidget(area);
    mSelectInformationWidget = new MergeContactSelectInformationWidget;
    mSelectInformationWidget->setObjectName(QStringLiteral("selectinformationwidget"));
    area->setWidget(mSelectInformationWidget);

    auto hbox = new QHBoxLayout;
    hbox->addStretch();
    auto mergeButton = new QPushButton(i18n("Merge"));
    mergeButton->setObjectName(QStringLiteral("merge"));
    hbox->addWidget(mergeButton);
    layout->addLayout(hbox);
    connect(mergeButton, &QPushButton::clicked, this, &MergeContactSelectInformationScrollArea::slotMergeContacts);

    mStackWidget->addWidget(selectMergeWidget);

    mMergedContactWidget = new MergeContactInfoWidget;
    mMergedContactWidget->setObjectName(QStringLiteral("mergedcontactwidget"));
    mStackWidget->addWidget(mMergedContactWidget);
    mStackWidget->setCurrentWidget(selectMergeWidget);
}

MergeContactSelectInformationScrollArea::~MergeContactSelectInformationScrollArea() = default;

void MergeContactSelectInformationScrollArea::setContacts(MergeContacts::ConflictInformations conflictTypes,
                                                          const Akonadi::Item::List &listItem,
                                                          const Akonadi::Collection &col)
{
    mCollection = col;
    mListItem = listItem;
    if (conflictTypes == MergeContacts::None) {
        MergeContacts contact(mListItem);
        KContacts::Addressee addr = contact.mergedContact();
        mergeContact(addr);
    } else {
        mSelectInformationWidget->setContacts(conflictTypes, listItem);
    }
}

void MergeContactSelectInformationScrollArea::slotMergeContacts()
{
    if (!mCollection.isValid()) {
        qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " Invalid collection";
        return;
    }
    if (mListItem.isEmpty()) {
        qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " item list is empty";
        return;
    }
    const bool result = mSelectInformationWidget->verifySelectedInfo();
    if (!result) {
        if (KMessageBox::No
            == KMessageBox::warningYesNo(this,
                                         i18n("Some information was not selected. You can lose this information. Do you want to continue merging?"),
                                         i18n("Missing Selected Information"),
                                         KStandardGuiItem::cont(),
                                         KStandardGuiItem::cancel())) {
            return;
        }
    }
    MergeContacts contact(mListItem);
    KContacts::Addressee addr = contact.mergedContact(true);
    mSelectInformationWidget->createContact(addr);
    mergeContact(addr);
}

void MergeContactSelectInformationScrollArea::mergeContact(const KContacts::Addressee &addr)
{
    if (!addr.isEmpty()) {
        auto job = new KABMergeContacts::MergeContactsJob(this);
        job->setNewContact(addr);
        job->setDestination(mCollection);
        job->setListItem(mListItem);
        connect(job, &MergeContactsJob::finished, this, &MergeContactSelectInformationScrollArea::slotMergeDone);
        job->start();
    } else {
        qCDebug(KADDRESSBOOKMERGELIBPRIVATE_LOG) << " Address is empty";
    }
}

void MergeContactSelectInformationScrollArea::slotMergeDone(const Akonadi::Item &item)
{
    mMergedContactWidget->setContact(item);
    mStackWidget->setCurrentWidget(mMergedContactWidget);
}
