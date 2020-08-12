/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINCREATETODO_H
#define VIEWERPLUGINCREATETODO_H

#include <MessageViewer/ViewerPlugin>
#include <QVariant>
namespace MessageViewer {
class ViewerPluginCreatetodo : public MessageViewer::ViewerPlugin
{
    Q_OBJECT
public:
    explicit ViewerPluginCreatetodo(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());

    ViewerPluginInterface *createView(QWidget *parent, KActionCollection *ac) override;
    QString viewerPluginName() const override;
};
}
#endif // VIEWERPLUGINCREATETODO_H
