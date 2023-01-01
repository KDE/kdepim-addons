/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "adblocklib_export.h"
#include <QListWidget>
namespace AdBlock
{
class ADBLOCKLIB_EXPORT AdBlockAutomaticRulesListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit AdBlockAutomaticRulesListWidget(QWidget *parent = nullptr);
    ~AdBlockAutomaticRulesListWidget() override;
    void setRules(const QString &rules);

    void setDisabledRules(const QStringList &disabledRules);
    Q_REQUIRED_RESULT QStringList disabledRules() const;

private:
    void slotItemChanged(QListWidgetItem *item);
    void updateItem(QListWidgetItem *item);
    void createItem(const QString &rule);
    QStringList mDisabledRules;
    QColor defaultTextColor;
};
}
