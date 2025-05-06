/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "pimautogeneratetext_export.h"
#include <KActionMenu>
class AutogenerateConfigureAskManager;
class PIMAUTOGENERATETEXT_EXPORT AutogenerateConfigureAskMenu : public KActionMenu
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskMenu(AutogenerateConfigureAskManager *manager, QObject *parent = nullptr);
    ~AutogenerateConfigureAskMenu() override;

    [[nodiscard]] QWidget *parentWidget() const;
    void setParentWidget(QWidget *newParentWidget);

    [[nodiscard]] QString selectedText() const;
    void setSelectedText(const QString &newSelectedText);

Q_SIGNALS:
    void askRequested(const QString &msg);

private:
    PIMAUTOGENERATETEXT_NO_EXPORT void initializeMenu();
    PIMAUTOGENERATETEXT_NO_EXPORT void slotConfigure();
    QString mSelectedText;
    QWidget *mParentWidget = nullptr;
    AutogenerateConfigureAskManager *const mManager;
};
