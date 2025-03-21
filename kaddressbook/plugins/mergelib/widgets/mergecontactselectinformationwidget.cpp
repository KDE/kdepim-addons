/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactselectinformationwidget.h"
#include "widgets/mergecontactselectlistwidget.h"

#include <QVBoxLayout>

using namespace KABMergeContacts;
MergeContactSelectInformationWidget::MergeContactSelectInformationWidget(QWidget *parent)
    : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
}

MergeContactSelectInformationWidget::~MergeContactSelectInformationWidget() = default;

void MergeContactSelectInformationWidget::setContacts(MergeContacts::ConflictInformations conflictTypes, const Akonadi::Item::List &listItem)
{
    for (const Akonadi::Item &item : listItem) {
        if (item.hasPayload<KContacts::Addressee>()) {
            const auto address = item.payload<KContacts::Addressee>();
            mAddressList.append(address);
        }
    }
    if (conflictTypes & MergeContacts::Birthday) {
        addInformationWidget(MergeContacts::Birthday);
    }
    if (conflictTypes & MergeContacts::Geo) {
        addInformationWidget(MergeContacts::Geo);
    }
    if (conflictTypes & MergeContacts::Photo) {
        addInformationWidget(MergeContacts::Photo);
    }
    if (conflictTypes & MergeContacts::Logo) {
        addInformationWidget(MergeContacts::Logo);
    }
    if (conflictTypes & MergeContacts::Anniversary) {
        addInformationWidget(MergeContacts::Anniversary);
    }
    if (conflictTypes & MergeContacts::Name) {
        addInformationWidget(MergeContacts::Name);
    }
    if (conflictTypes & MergeContacts::NickName) {
        addInformationWidget(MergeContacts::NickName);
    }
    if (conflictTypes & MergeContacts::Blog) {
        addInformationWidget(MergeContacts::Blog);
    }
    if (conflictTypes & MergeContacts::HomePage) {
        addInformationWidget(MergeContacts::HomePage);
    }
    if (conflictTypes & MergeContacts::Organization) {
        addInformationWidget(MergeContacts::Organization);
    }
    if (conflictTypes & MergeContacts::Profession) {
        addInformationWidget(MergeContacts::Profession);
    }
    if (conflictTypes & MergeContacts::Title) {
        addInformationWidget(MergeContacts::Title);
    }
    if (conflictTypes & MergeContacts::Departement) {
        addInformationWidget(MergeContacts::Departement);
    }
    if (conflictTypes & MergeContacts::Office) {
        addInformationWidget(MergeContacts::Office);
    }
    if (conflictTypes & MergeContacts::ManagerName) {
        addInformationWidget(MergeContacts::ManagerName);
    }
    if (conflictTypes & MergeContacts::Assistant) {
        addInformationWidget(MergeContacts::Assistant);
    }
    if (conflictTypes & MergeContacts::FreeBusy) {
        addInformationWidget(MergeContacts::FreeBusy);
    }
    if (conflictTypes & MergeContacts::FamilyName) {
        addInformationWidget(MergeContacts::FamilyName);
    }
    if (conflictTypes & MergeContacts::PartnerName) {
        addInformationWidget(MergeContacts::PartnerName);
    }
    if (conflictTypes & MergeContacts::Keys) {
        addInformationWidget(MergeContacts::Keys);
    }
}

void MergeContactSelectInformationWidget::addInformationWidget(MergeContacts::ConflictInformation conflictType)
{
    auto widget = new MergeContactSelectListWidget;
    widget->setContacts(conflictType, mAddressList);
    layout()->addWidget(widget);
    mListMergeSelectInformation.append(widget);
}

bool MergeContactSelectInformationWidget::verifySelectedInfo() const
{
    bool result = true;
    for (MergeContactSelectListWidget *listWidget : std::as_const(mListMergeSelectInformation)) {
        result = listWidget->verifySelectedInfo();
        if (!result) {
            break;
        }
    }
    return result;
}

void MergeContactSelectInformationWidget::createContact(KContacts::Addressee &addr)
{
    for (MergeContactSelectListWidget *listWidget : std::as_const(mListMergeSelectInformation)) {
        const int selectedContactIndex = listWidget->selectedContact();
        const MergeContacts::ConflictInformation conflictType = listWidget->conflictType();
        if (selectedContactIndex != -1) {
            switch (conflictType) {
            case MergeContacts::None:
                break;
            case MergeContacts::Birthday:
                addr.setBirthday(mAddressList.at(selectedContactIndex).birthday());
                break;
            case MergeContacts::Geo:
                addr.setGeo(mAddressList.at(selectedContactIndex).geo());
                break;
            case MergeContacts::Photo:
                addr.setPhoto(mAddressList.at(selectedContactIndex).photo());
                break;
            case MergeContacts::Logo:
                addr.setLogo(mAddressList.at(selectedContactIndex).logo());
                break;
            case MergeContacts::Anniversary:
                addr.setBirthday(mAddressList.at(selectedContactIndex).birthday());
                break;
            case MergeContacts::Name:
                addr.setName(mAddressList.at(selectedContactIndex).name());
                break;
            case MergeContacts::NickName:
                addr.setNickName(mAddressList.at(selectedContactIndex).nickName());
                break;
            case MergeContacts::Blog: {
                const QString newBlog = mAddressList.at(selectedContactIndex).custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("BlogFeed"));
                addr.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("BlogFeed"), newBlog);
                break;
            }
            case MergeContacts::HomePage:
                addr.setUrl(mAddressList.at(selectedContactIndex).url());
                break;
            case MergeContacts::Organization:
                addr.setOrganization(mAddressList.at(selectedContactIndex).organization());
                break;
            case MergeContacts::Profession: {
                const QString newValue = mAddressList.at(selectedContactIndex).custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Profession"));
                addr.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Profession"), newValue);
                break;
            }
            case MergeContacts::Title:
                addr.setTitle(mAddressList.at(selectedContactIndex).title());
                break;
            case MergeContacts::Departement:
                addr.setDepartment(mAddressList.at(selectedContactIndex).department());
                break;
            case MergeContacts::Office: {
                const QString newValue = mAddressList.at(selectedContactIndex).custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Office"));
                addr.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-Office"), newValue);
                break;
            }
            case MergeContacts::ManagerName: {
                const QString newValue = mAddressList.at(selectedContactIndex).custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-ManagersName"));
                addr.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-ManagersName"), newValue);
                break;
            }
            case MergeContacts::Assistant: {
                const QString newValue = mAddressList.at(selectedContactIndex).custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-AssistantsName"));
                addr.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-AssistantsName"), newValue);
                break;
            }
            case MergeContacts::FreeBusy:
                // TODO
                break;
            case MergeContacts::FamilyName:
                addr.setFamilyName(mAddressList.at(selectedContactIndex).familyName());
                break;
            case MergeContacts::PartnerName: {
                const QString newValue = mAddressList.at(selectedContactIndex).custom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-SpousesName"));
                addr.insertCustom(QStringLiteral("KADDRESSBOOK"), QStringLiteral("X-SpousesName"), newValue);
                break;
            }
            case MergeContacts::Keys:
                addr.setKeys(mAddressList.at(selectedContactIndex).keys());
                break;
            }
        }
    }
}

#include "moc_mergecontactselectinformationwidget.cpp"
