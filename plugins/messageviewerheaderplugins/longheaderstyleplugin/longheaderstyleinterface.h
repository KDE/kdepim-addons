/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LONGHEADERSTYLEINTERFACE_H
#define LONGHEADERSTYLEINTERFACE_H

#include <MessageViewer/HeaderStyleInterface>

namespace MessageViewer {
class LongHeaderStyleInterface : public MessageViewer::HeaderStyleInterface
{
    Q_OBJECT
public:
    explicit LongHeaderStyleInterface(HeaderStylePlugin *plugin, QObject *parent = nullptr);
    ~LongHeaderStyleInterface() override;

    void createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac) override;
    void activateAction() override;
};
}

#endif // LONGHEADERSTYLEINTERFACE_H
