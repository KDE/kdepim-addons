/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef VIEWERPLUGINEXPANDURLINTERFACE_H
#define VIEWERPLUGINEXPANDURLINTERFACE_H

#include <messageviewer/viewerplugininterface.h>
#include <QUrl>
class KActionCollection;
namespace MessageViewer {
class ViewerPluginExpandurlInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginExpandurlInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginExpandurlInterface();

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
