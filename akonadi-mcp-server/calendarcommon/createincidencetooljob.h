/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"
#include <Akonadi/Collection>
#include <KCalendarCore/Incidence>

class CreateIncidenceToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit CreateIncidenceToolJob(QObject *parent = nullptr);
    ~CreateIncidenceToolJob() override;

    void setIncidence(const KCalendarCore::Incidence::Ptr &incidence);

    [[nodiscard]] bool canStart() const override;

    void setCalendarId(Akonadi::Collection::Id id);

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotCollectionFetchResult(KJob *job);
    void slotItemCreateResult(KJob *job);
    void createIncidence(const Akonadi::Collection &collection);
    KCalendarCore::Incidence::Ptr mIncidence;
    Akonadi::Collection::Id mCalendarId = -1;
};
