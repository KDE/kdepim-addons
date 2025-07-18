/*
  SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingmanager.h"
using namespace Qt::Literals::StringLiterals;

#include <KConfigGroup>
#include <QRegularExpression>

ConfirmBeforeDeletingManager::ConfirmBeforeDeletingManager(QObject *parent)
    : QObject(parent)
{
    loadRules();
}

ConfirmBeforeDeletingManager::~ConfirmBeforeDeletingManager() = default;

ConfirmBeforeDeletingManager *ConfirmBeforeDeletingManager::self()
{
    static ConfirmBeforeDeletingManager s_self;
    return &s_self;
}

QString ConfirmBeforeDeletingManager::defaultConfigFileName() const
{
    return u"confirmbeforedeletingrc"_s;
}

void ConfirmBeforeDeletingManager::loadRules()
{
    const KSharedConfig::Ptr &config = KSharedConfig::openConfig(defaultConfigFileName(), KConfig::NoGlobals);
    const QStringList rulesGroups = ruleGroups(config);

    mRules.clear();
    for (const QString &groupName : rulesGroups) {
        ConfirmBeforeDeletingRule r;
        KConfigGroup group = config->group(groupName);
        r.load(group);
        if (r.isValid()) {
            mRules.append(r);
        }
    }
}

QString defaultGroupName()
{
    return u"Confirm Deleting Rule"_s;
}

QStringList ConfirmBeforeDeletingManager::ruleGroups(const KSharedConfig::Ptr &config) const
{
    return config->groupList().filter(QRegularExpression(defaultGroupName() + u" #\\d+"_s));
}

void ConfirmBeforeDeletingManager::setRules(const QList<ConfirmBeforeDeletingRule> &newRules)
{
    mRules = newRules;
}

const QList<ConfirmBeforeDeletingRule> &ConfirmBeforeDeletingManager::rules() const
{
    return mRules;
}

void ConfirmBeforeDeletingManager::saveRules()
{
    const KSharedConfig::Ptr &config = KSharedConfig::openConfig(defaultConfigFileName(), KConfig::NoGlobals);
    const QStringList rulesGroups = ruleGroups(config);

    for (const QString &group : rulesGroups) {
        config->deleteGroup(group);
    }
    for (int i = 0, total = mRules.count(); i < total; ++i) {
        const QString groupName = defaultGroupName() + u" #%1"_s.arg(i);
        KConfigGroup group = config->group(groupName);
        const ConfirmBeforeDeletingRule &rule = mRules.at(i);
        rule.save(group);
    }
}

bool ConfirmBeforeDeletingManager::deletingNeedToConfirm(const Akonadi::Item &item, QString &checkFound, ConfirmBeforeDeletingRule &rule) const
{
    for (const auto &r : std::as_const(mRules)) {
        if (r.deletingNeedToConfirm(item, checkFound)) {
            rule = r;
            return true;
        }
    }
    return false;
}

#include "moc_confirmbeforedeletingmanager.cpp"
