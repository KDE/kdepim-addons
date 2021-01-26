/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINTRANSLATOR_H
#define VIEWERPLUGINTRANSLATOR_H

#include <MessageViewer/ViewerPlugin>
#include <QVariant>
namespace MessageViewer
{
class ViewerPluginTranslator : public MessageViewer::ViewerPlugin
{
    Q_OBJECT
public:
    explicit ViewerPluginTranslator(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());

    ViewerPluginInterface *createView(QWidget *parent, KActionCollection *ac) override;
    QString viewerPluginName() const override;
};
}
#endif // VIEWERPLUGINTRANSLATOR_H
