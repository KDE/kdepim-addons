/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "confirmbeforedeletingrule.h"
#include "kmailconfirmbeforedeleting_export.h"
#include <Akonadi/Item>
#include <KSharedConfig>
#include <QObject>
#include <QVector>

class KMAILCONFIRMBEFOREDELETING_EXPORT ConfirmBeforeDeletingManager : public QObject
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingManager(QObject *parent = nullptr);
    ~ConfirmBeforeDeletingManager() override;

    static ConfirmBeforeDeletingManager *self();

    void loadRules();
    void saveRules();

    Q_REQUIRED_RESULT bool deletingNeedToConfirm(const Akonadi::Item &list, QString &checkFound, ConfirmBeforeDeletingRule &rule) const;

    Q_REQUIRED_RESULT const QVector<ConfirmBeforeDeletingRule> &rules() const;

    void setRules(const QVector<ConfirmBeforeDeletingRule> &newRules);

private:
    Q_REQUIRED_RESULT QString defaultConfigFileName() const;
    Q_REQUIRED_RESULT QStringList ruleGroups(const KSharedConfig::Ptr &config) const;
    QVector<ConfirmBeforeDeletingRule> mRules;
};
