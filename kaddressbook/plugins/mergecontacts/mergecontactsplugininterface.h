/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MERGECONTACTSPLUGININTERFACE_H
#define MERGECONTACTSPLUGININTERFACE_H

#include <PimCommonAkonadi/GenericPluginInterface>

class MergeContactsPluginInterface : public PimCommon::GenericPluginInterface
{
public:
    explicit MergeContactsPluginInterface(QObject *parent = nullptr);
    ~MergeContactsPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;
    void setCurrentItems(const Akonadi::Item::List &items) override;
    Q_REQUIRED_RESULT PimCommon::GenericPluginInterface::RequireTypes requires() const override;

private:
    void slotActivated();
    Akonadi::Item::List mListItems;
};

#endif // MERGECONTACTSPLUGININTERFACE_H
