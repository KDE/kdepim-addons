/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINCREATENOTE_H
#define VIEWERPLUGINCREATENOTE_H

#include <MessageViewer/ViewerPlugin>
#include <QVariant>
namespace MessageViewer {
class ViewerPluginCreatenote : public MessageViewer::ViewerPlugin
{
    Q_OBJECT
public:
    explicit ViewerPluginCreatenote(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());

    ViewerPluginInterface *createView(QWidget *parent, KActionCollection *ac) override;
    Q_REQUIRED_RESULT QString viewerPluginName() const override;
};
}
#endif // VIEWERPLUGINCREATENOTE_H
