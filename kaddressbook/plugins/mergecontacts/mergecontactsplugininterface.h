/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonAkonadi/GenericPluginInterface>

class MergeContactsPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit MergeContactsPluginInterface(QObject *parent = nullptr);
    ~MergeContactsPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;
    void setCurrentItems(const Akonadi::Item::List &items) override;
    Q_REQUIRED_RESULT PimCommon::GenericPluginInterface::RequireTypes requiresFeatures() const override;

private:
    void slotActivated();
    Akonadi::Item::List mListItems;
};
