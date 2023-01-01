/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/ViewerPluginInterface>
#include <QUrl>
class KActionCollection;
namespace MessageViewer
{
class ViewerPluginExpandurlInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginExpandurlInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginExpandurlInterface() override;

    Q_REQUIRED_RESULT QList<QAction *> actions() const override;
    void execute() override;
    Q_REQUIRED_RESULT ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;

    void setUrl(const QUrl &url) override;

private:
    void createAction(KActionCollection *ac);
    QUrl mCurrentUrl;
    QList<QAction *> mAction;
};
}
