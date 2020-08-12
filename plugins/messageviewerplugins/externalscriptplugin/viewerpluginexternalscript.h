/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALSCRIPT_H
#define VIEWERPLUGINEXTERNALSCRIPT_H

#include <MessageViewer/ViewerPlugin>
#include <QVariant>
namespace MessageViewer {
class ViewerPluginExternalscript : public MessageViewer::ViewerPlugin
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalscript(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());

    ViewerPluginInterface *createView(QWidget *parent, KActionCollection *ac) override;
    QString viewerPluginName() const override;

    void showConfigureDialog(QWidget *parent) override;
    bool hasConfigureDialog() const override;
};
}
#endif // VIEWERPLUGINEXTERNALSCRIPT_H
