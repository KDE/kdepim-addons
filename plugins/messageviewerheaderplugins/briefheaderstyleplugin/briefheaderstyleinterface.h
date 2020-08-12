/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef BRIEFHEADERSTYLEINTERFACE_H
#define BRIEFHEADERSTYLEINTERFACE_H

#include <MessageViewer/HeaderStyleInterface>

class KActionCollection;
namespace MessageViewer {
class BriefHeaderStyleInterface : public MessageViewer::HeaderStyleInterface
{
    Q_OBJECT
public:
    explicit BriefHeaderStyleInterface(MessageViewer::HeaderStylePlugin *plugin, QObject *parent = nullptr);
    ~BriefHeaderStyleInterface() override;

    void createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac) override;
    void activateAction() override;
};
}

#endif // BRIEFHEADERSTYLEINTERFACE_H
