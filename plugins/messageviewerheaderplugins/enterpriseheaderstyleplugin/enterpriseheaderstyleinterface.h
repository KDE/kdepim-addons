/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ENTERPRISEHEADERSTYLEINTERFACE_H
#define ENTERPRISEHEADERSTYLEINTERFACE_H

#include <MessageViewer/HeaderStyleInterface>

namespace MessageViewer {
class EnterpriseHeaderStyleInterface : public MessageViewer::HeaderStyleInterface
{
    Q_OBJECT
public:
    explicit EnterpriseHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent = nullptr);
    ~EnterpriseHeaderStyleInterface() override;

    void createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac) override;
    void activateAction() override;
};
}

#endif // ENTERPRISEHEADERSTYLEINTERFACE_H
