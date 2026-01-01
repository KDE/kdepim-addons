/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class MergeContactsTest : public QObject
{
    Q_OBJECT
public:
    explicit MergeContactsTest(QObject *parent = nullptr);

private Q_SLOTS:
    void shouldReturnDefaultAddressWhenNoListItem();
    void shouldReturnDefaultAddressWhenOneItem();
    void noNeedManualSelectionCheckWhenEmptyList();
    void noNeedManualSelectionCheckWhenOneItem();

    void checkNeedManualSelectionWithName_data();
    void checkNeedManualSelectionWithName();

    void checkNeedManualSelectionWithNickName_data();
    void checkNeedManualSelectionWithNickName();

    void checkNeedManualSelectionWithOrganization_data();
    void checkNeedManualSelectionWithOrganization();

    void checkNeedManualSelectionWithTitle_data();
    void checkNeedManualSelectionWithTitle();

    void checkNeedManualSelectionWithDepartement_data();
    void checkNeedManualSelectionWithDepartement();

    void checkNeedManualSelectionWithHomePage_data();
    void checkNeedManualSelectionWithHomePage();

    void checkNeedManualSelectionWithFamilyName_data();
    void checkNeedManualSelectionWithFamilyName();

    void checkNeedManualSelectionWithBlog_data();
    void checkNeedManualSelectionWithBlog();

    void checkNeedManualSelectionWithProfession_data();
    void checkNeedManualSelectionWithProfession();

    void checkNeedManualSelectionWithOffice_data();
    void checkNeedManualSelectionWithOffice();

    void checkNeedManualSelectionWithManagerName();
    void checkNeedManualSelectionWithManagerName_data();

    void checkNeedManualSelectionWithAssistantName_data();
    void checkNeedManualSelectionWithAssistantName();

    void shouldMergeNotes_data();
    void shouldMergeNotes();
    void shouldMergeEmails_data();
    void shouldMergeEmails();

    void checkNeedManualSelectionWithPartnersName();
    void checkNeedManualSelectionWithPartnersName_data();

    void checkNeedManualSelectionWithAnniversary_data();
    void checkNeedManualSelectionWithAnniversary();

    void shouldMergeTitle_data();
    void shouldMergeTitle();

    void shouldMergeDepartement_data();
    void shouldMergeDepartement();
    void shouldMergeFamilyname();
    void shouldMergeFamilyname_data();
    void shouldMergeHomePage_data();
    void shouldMergeHomePage();

    void shouldMergeBlogFeed();
    void shouldMergeBlogFeed_data();

    void checkNeedManualSelectionWithBirthday_data();
    void checkNeedManualSelectionWithBirthday();
};
