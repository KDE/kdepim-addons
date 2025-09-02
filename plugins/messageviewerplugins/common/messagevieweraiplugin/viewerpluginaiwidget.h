/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
class QToolButton;
class ViewerPluginAIWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewerPluginAIWidget(QWidget *parent = nullptr);
    ~ViewerPluginAIWidget() override;

private:
    void slotCloseWidget();
    QToolButton *const mCloseButton;
};
