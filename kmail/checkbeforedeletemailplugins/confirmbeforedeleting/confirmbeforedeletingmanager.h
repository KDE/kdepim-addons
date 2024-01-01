/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "confirmbeforedeletingrule.h"
#include "kmailconfirmbeforedeleting_export.h"
#include <Akonadi/Item>
#include <KSharedConfig>
#include <QList>
#include <QObject>

class KMAILCONFIRMBEFOREDELETING_EXPORT ConfirmBeforeDeletingManager : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingManager(QObject *parent = nullptr);
    ~ConfirmBeforeDeletingManager() override;

    static ConfirmBeforeDeletingManager *self();

    void loadRules();
    void saveRules();

    [[nodiscard]] bool deletingNeedToConfirm(const Akonadi::Item &list, QString &checkFound, ConfirmBeforeDeletingRule &rule) const;

    [[nodiscard]] const QList<ConfirmBeforeDeletingRule> &rules() const;

    void setRules(const QList<ConfirmBeforeDeletingRule> &newRules);

private:
    [[nodiscard]] QString defaultConfigFileName() const;
    [[nodiscard]] QStringList ruleGroups(const KSharedConfig::Ptr &config) const;
    QList<ConfirmBeforeDeletingRule> mRules;
};
