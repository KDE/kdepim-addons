/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonAkonadi/GenericPluginInterface>

class SendVcardsPluginInterface : public PimCommon::GenericPluginInterface
{
    Q_OBJECT
public:
    explicit SendVcardsPluginInterface(QObject *parent = nullptr);
    ~SendVcardsPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;
    void setCurrentItems(const Akonadi::Item::List &items) override;
    Q_REQUIRED_RESULT PimCommon::GenericPluginInterface::RequireTypes requiresFeatures() const override;

    void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections) override;

private:
    void slotActivated();
    void slotSendVcardsError(const QString &error);
    Akonadi::Item::List mListItems;
    QAction *mAction = nullptr;
};
