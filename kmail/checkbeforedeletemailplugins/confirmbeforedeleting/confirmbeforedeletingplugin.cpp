/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingplugin.h"
#include "confirmbeforedeletingdialog.h"
#include <QPointer>

ConfirmBeforeDeletingPlugin::ConfirmBeforeDeletingPlugin(QObject *parent)
    : MessageViewer::MessageViewerCheckBeforeDeletingPlugin(parent)
{
}

ConfirmBeforeDeletingPlugin::~ConfirmBeforeDeletingPlugin()
{
}

void ConfirmBeforeDeletingPlugin::showConfigureDialog(QWidget *parent)
{
    QPointer<ConfirmBeforeDeletingDialog> dlg = new ConfirmBeforeDeletingDialog(parent);
    if (dlg->exec()) {
        // TODO
    }
    delete dlg;
}
