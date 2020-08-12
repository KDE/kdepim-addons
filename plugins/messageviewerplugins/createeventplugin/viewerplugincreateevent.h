/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINCREATEEVENT_H
#define VIEWERPLUGINCREATEEVENT_H
#include <MessageViewer/ViewerPlugin>
#include <QVariant>
namespace MessageViewer {
class ViewerPluginCreateevent : public MessageViewer::ViewerPlugin
{
    Q_OBJECT
public:
    explicit ViewerPluginCreateevent(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());

    ViewerPluginInterface *createView(QWidget *parent, KActionCollection *ac) override;
    QString viewerPluginName() const override;
};
}
#endif // VIEWERPLUGINCREATEEVENT_H
