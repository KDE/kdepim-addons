/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/ViewerPlugin>
#include <QVariant>
namespace MessageViewer
{
class ViewerPluginExpandurl : public MessageViewer::ViewerPlugin
{
    Q_OBJECT
public:
    explicit ViewerPluginExpandurl(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());

    [[nodiscard]] ViewerPluginInterface *createView(QWidget *parent, KActionCollection *ac) override;
    [[nodiscard]] QString viewerPluginName() const override;
};
}
