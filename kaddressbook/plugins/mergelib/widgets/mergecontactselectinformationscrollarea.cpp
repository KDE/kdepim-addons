/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactselectinformationscrollarea.h"
#include "mergecontactselectinformationwidget.h"
#include "job/mergecontactsjob.h"
#include "widgets/mergecontactinfowidget.h"
#include "kaddressbookmergelibprivate_debug.h"
#include <KLocalizedString>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStackedWidget>
#include <QPushButton>
#include <KMessageBox>
using namespace KABMergeContacts;

MergeContactSelectInformationScrollArea::MergeContactSelectInformationScrollArea(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    mStackWidget = new QStackedWidget;
    mStackWidget->setObjectName(QStringLiteral("stackwidget"));
    vbox->addWidget(mStackWidget);

    QWidget *selectMergeWidget = new QWidget;
    selectMergeWidget->setObjectName(QStringLiteral("selectwidget"));
    QVBoxLayout *layout = new QVBoxLayout;
    selectMergeWidget->setLayout(layout);
    QScrollArea *area = new QScrollArea;
    area->setWidgetResizable(true);
    area->setObjectName(QStringLiteral("scrollarea"));
    layout->addWidget(area);
    mSelectInformationWidget = new MergeContactSelectInformationWidget;
    mSelectInformationWidget->setObjectName(QStringLiteral("selectinformationwidget"));
    area->setWidget(mSelectInformationWidget);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addStretch();
    QPushButton *mergeButton = new QPushButton(i18n("Merge"));
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

MergeContactSelectInformationScrollArea::~MergeContactSelectInformationScrollArea()
{
}

void MergeContactSelectInformationScrollArea::setContacts(MergeContacts::ConflictInformations conflictTypes, const Akonadi::Item::List &listItem, const Akonadi::Collection &col)
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
        if (KMessageBox::No == KMessageBox::warningYesNo(this, i18n("Some information was not selected. You can lose this information. Do you want to continue merging?"),
                                                         i18n("Missing Selected Information"))) {
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
        KABMergeContacts::MergeContactsJob *job = new KABMergeContacts::MergeContactsJob(this);
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
