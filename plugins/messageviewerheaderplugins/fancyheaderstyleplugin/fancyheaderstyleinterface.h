/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef FANCYHEADERSTYLEINTERFACE_H
#define FANCYHEADERSTYLEINTERFACE_H

#include <MessageViewer/HeaderStyleInterface>

namespace MessageViewer {
class FancyHeaderStyleInterface : public MessageViewer::HeaderStyleInterface
{
    Q_OBJECT
public:
    explicit FancyHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent = nullptr);
    ~FancyHeaderStyleInterface() override;

    void createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac) override;
    void activateAction() override;
};
}

#endif // FANCYHEADERSTYLEINTERFACE_H
