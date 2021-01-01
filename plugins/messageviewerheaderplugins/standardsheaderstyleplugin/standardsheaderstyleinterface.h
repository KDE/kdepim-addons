/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef STANDARDSHEADERSTYLEINTERFACE_H
#define STANDARDSHEADERSTYLEINTERFACE_H

#include <MessageViewer/HeaderStyleInterface>

namespace MessageViewer {
class StandardsHeaderStyleInterface : public MessageViewer::HeaderStyleInterface
{
    Q_OBJECT
public:
    explicit StandardsHeaderStyleInterface(HeaderStylePlugin *plugin, QObject *parent = nullptr);
    ~StandardsHeaderStyleInterface() override;

    void createAction(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac) override;
    void activateAction() override;
};
}

#endif // STANDARDSHEADERSTYLEINTERFACE_H
