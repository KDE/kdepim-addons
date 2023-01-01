/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/ViewerPlugin>
#include <QVariant>
namespace MessageViewer
{
class ViewerPluginCreatetodo : public MessageViewer::ViewerPlugin
{
    Q_OBJECT
public:
    explicit ViewerPluginCreatetodo(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());

    Q_REQUIRED_RESULT ViewerPluginInterface *createView(QWidget *parent, KActionCollection *ac) override;
    Q_REQUIRED_RESULT QString viewerPluginName() const override;
};
}
