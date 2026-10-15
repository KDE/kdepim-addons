/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "common/tooljobbase.h"

class SearchMailToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    enum class SearchField : uint8_t {
        All,
        Subject,
        From,
        To,
        Body,
    };

    explicit SearchMailToolJob(QObject *parent = nullptr);
    ~SearchMailToolJob() override;

    void setSearchString(const QString &str);

    void setSearchField(SearchField field);

    void setLimit(int limit);

    [[nodiscard]] bool canStart() const override;

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotResult(KJob *job);
    QString mSearchString;
    SearchField mSearchField = SearchField::All;
    int mLimit = 20;
};
