/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QStringList>

class CheckAttachmentJob
{
public:
    CheckAttachmentJob();
    ~CheckAttachmentJob();

    void start();

    [[nodiscard]] QStringList originalEmails() const;
    void setOriginalEmails(const QStringList &originalEmails);

    [[nodiscard]] QStringList resultList() const;
    void setResultList(const QStringList &resultList);

private:
    QStringList mOriginalEmails;
    QStringList mResultList;
};
