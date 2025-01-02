/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <MessageViewer/ViewerPlugin>
#include <QVariant>
namespace MessageViewer
{
class ViewerPluginCreateevent : public MessageViewer::ViewerPlugin
{
    Q_OBJECT
public:
    explicit ViewerPluginCreateevent(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());

    ViewerPluginInterface *createView(QWidget *parent, KActionCollection *ac) override;
    [[nodiscard]] QString viewerPluginName() const override;
};
}
