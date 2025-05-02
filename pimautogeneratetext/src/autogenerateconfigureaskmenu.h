/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimautogeneratetext_export.h"
#include <QObject>
class QMenu;
class AutogenerateConfigureAskManager;
class PIMAUTOGENERATETEXT_EXPORT AutogenerateConfigureAskMenu : public QObject
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskMenu(AutogenerateConfigureAskManager *manager, QObject *parent = nullptr);
    ~AutogenerateConfigureAskMenu() override;

    [[nodiscard]] QWidget *parentWidget() const;
    void setParentWidget(QWidget *newParentWidget);

    [[nodiscard]] QMenu *menu() const;

Q_SIGNALS:
    void askRequested(const QString &msg);

private:
    PIMAUTOGENERATETEXT_NO_EXPORT void initializeMenu();
    PIMAUTOGENERATETEXT_NO_EXPORT void slotConfigure();
    QWidget *mParentWidget = nullptr;
    AutogenerateConfigureAskManager *const mManager;
    QMenu *const mMenu;
};
