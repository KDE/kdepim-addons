/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"
#include <KContacts/ContactGroup>
#include <QStringList>

class ContactGroupExpandToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit ContactGroupExpandToolJob(QObject *parent = nullptr);
    ~ContactGroupExpandToolJob() override;

    void setGroupName(const QString &str);

    [[nodiscard]] bool canStart() const override;

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotResult(KJob *job);
    void slotExpandResult(KJob *job);
    void expandNextGroup();
    KContacts::ContactGroup::List mContactGroups;
    QStringList mEntries;
    QString mSearchString;
};
