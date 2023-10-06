/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommonAkonadi/GenericPluginInterface>

class SendMailPluginInterface : public PimCommon::GenericPluginInterface
{
    Q_OBJECT
public:
    explicit SendMailPluginInterface(QObject *parent = nullptr);
    ~SendMailPluginInterface() override;

    void exec() override;
    void createAction(KActionCollection *ac) override;
    void setCurrentItems(const Akonadi::Item::List &items) override;
    [[nodiscard]] PimCommon::GenericPluginInterface::RequireTypes requiresFeatures() const override;
    void updateActions(int numberOfSelectedItems, int numberOfSelectedCollections) override;

private:
    void slotActivated();
    void slotSendMailError(const QString &error);
    void slotSendMails(const QStringList &emails);
    Akonadi::Item::List mListItems;
    QAction *mAction = nullptr;
};
