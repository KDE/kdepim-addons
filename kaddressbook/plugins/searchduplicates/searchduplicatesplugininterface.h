/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonAkonadi/GenericPluginInterface>

class SearchDuplicatesPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit SearchDuplicatesPluginInterface(QObject *parent = nullptr);
    ~SearchDuplicatesPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;
    Q_REQUIRED_RESULT PimCommon::GenericPluginInterface::RequireTypes requiresFeatures() const override;
    void setItems(const Akonadi::Item::List &items) override;

private:
    void slotActivated();
    Akonadi::Item::List mListItems;
};
