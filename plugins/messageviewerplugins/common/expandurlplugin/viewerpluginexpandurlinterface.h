/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXPANDURLINTERFACE_H
#define VIEWERPLUGINEXPANDURLINTERFACE_H

#include <MessageViewer/ViewerPluginInterface>
#include <QUrl>
class KActionCollection;
namespace MessageViewer {
class ViewerPluginExpandurlInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginExpandurlInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginExpandurlInterface() override;

    QList<QAction *> actions() const override;
    void execute() override;
    ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;

    void setUrl(const QUrl &url) override;
private:
    void createAction(KActionCollection *ac);
    QUrl mCurrentUrl;
    QList<QAction *> mAction;
};
}
#endif // VIEWERPLUGINEXPANDURLINTERFACE_H
