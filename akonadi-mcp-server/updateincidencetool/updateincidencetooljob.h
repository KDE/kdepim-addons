/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "calendarcommon/calendartoolutils.h"
#include "common/tooljobbase.h"
#include <KCalendarCore/Incidence>
#include <optional>

class UpdateIncidenceToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    struct IncidenceChanges {
        std::optional<QString> summary;
        std::optional<QString> description;
        std::optional<QString> location;
        std::optional<CalendarToolUtils::IncidenceDateTime> start;
        // Events only
        std::optional<CalendarToolUtils::IncidenceDateTime> end;
        // To-dos only, an invalid date-time clears the due date
        std::optional<CalendarToolUtils::IncidenceDateTime> due;
        // To-dos only, 0 means undefined
        std::optional<int> priority;
        // To-dos only
        std::optional<bool> completed;
        [[nodiscard]] bool isEmpty() const;
    };

    explicit UpdateIncidenceToolJob(QObject *parent = nullptr);
    ~UpdateIncidenceToolJob() override;

    [[nodiscard]] bool canStart() const override;

    void setItemId(qint64 itemId);
    void setChanges(const IncidenceChanges &changes);

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotItemFetchResult(KJob *job);
    void slotItemModifyResult(KJob *job);
    // Returns an error message, or an empty string on success
    [[nodiscard]] QString applyChanges(const KCalendarCore::Incidence::Ptr &incidence) const;
    [[nodiscard]] QString applyEventChanges(const KCalendarCore::Incidence::Ptr &incidence) const;
    [[nodiscard]] QString applyTodoChanges(const KCalendarCore::Incidence::Ptr &incidence) const;
    qint64 mItemId = -1;
    IncidenceChanges mChanges;
};
