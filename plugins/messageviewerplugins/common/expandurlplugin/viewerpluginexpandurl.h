/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXPANDURL_H
#define VIEWERPLUGINEXPANDURL_H

#include <MessageViewer/ViewerPlugin>
#include <QVariant>
namespace MessageViewer {
class ViewerPluginExpandurl : public MessageViewer::ViewerPlugin
{
    Q_OBJECT
public:
    explicit ViewerPluginExpandurl(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());

    ViewerPluginInterface *createView(QWidget *parent, KActionCollection *ac) override;
    QString viewerPluginName() const override;
};
}
#endif // VIEWERPLUGINEXPANDURL_H
