/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKAUTOMATICRULESLISTWIDGET_H
#define ADBLOCKAUTOMATICRULESLISTWIDGET_H

#include <QListWidget>
#include "adblocklib_export.h"
namespace AdBlock {
class ADBLOCKLIB_EXPORT AdBlockAutomaticRulesListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit AdBlockAutomaticRulesListWidget(QWidget *parent = nullptr);
    ~AdBlockAutomaticRulesListWidget();
    void setRules(const QString &rules);

    void setDisabledRules(const QStringList &disabledRules);
    QStringList disabledRules() const;

private:
    void slotItemChanged(QListWidgetItem *item);
    void updateItem(QListWidgetItem *item);
    void createItem(const QString &rule);
    QStringList mDisabledRules;
    QColor defaultTextColor;
};
}

#endif // ADBLOCKAUTOMATICRULESLISTWIDGET_H
