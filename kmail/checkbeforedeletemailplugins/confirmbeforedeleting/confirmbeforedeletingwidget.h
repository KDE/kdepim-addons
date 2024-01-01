/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "confirmbeforedeleting_private_export.h"
#include "confirmbeforedeletingcreaterulewidget.h"
#include <QWidget>
class QTreeWidget;
class QTreeWidgetItem;
class QPushButton;
class KMAILCONFIRMBEFOREDELETING_TESTS_EXPORT ConfirmBeforeDeletingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfirmBeforeDeletingWidget(QWidget *parent = nullptr);
    ~ConfirmBeforeDeletingWidget() override;

    void save();

private:
    void slotCustomContextMenuRequested(const QPoint &p);
    void slotRemoveRule();
    void slotAddRule();
    void fillRules();
    void slotEditRule();
    void initializeItem(QTreeWidgetItem *item, const ConfirmBeforeDeletingCreateRuleWidget::ConfirmBeforeDeletingInfo &info);
    void updateButtons();
    QTreeWidget *const mTreeWidget;
    QPushButton *const mAddRule;
    QPushButton *const mRemoveRule;
    QPushButton *const mModifyRule;
};
