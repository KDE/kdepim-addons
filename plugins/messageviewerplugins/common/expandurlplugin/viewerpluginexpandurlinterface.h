/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef VIEWERPLUGINEXPANDURLINTERFACE_H
#define VIEWERPLUGINEXPANDURLINTERFACE_H

#include <messageviewer/viewerplugininterface.h>
#include <QUrl>
class KActionCollection;
namespace MessageViewer
{
class ViewerPluginExpandurlInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginExpandurlInterface(KActionCollection *ac, QWidget *parent = Q_NULLPTR);
    ~ViewerPluginExpandurlInterface();

    QList<QAction *> actions() const Q_DECL_OVERRIDE;
    void execute() Q_DECL_OVERRIDE;
    ViewerPluginInterface::SpecificFeatureTypes featureTypes() const Q_DECL_OVERRIDE;

    void setUrl(const QUrl &url) Q_DECL_OVERRIDE;
private:
    void createAction(KActionCollection *ac);
    QUrl mCurrentUrl;
    QList<QAction *> mAction;
};
}
#endif // VIEWERPLUGINEXPANDURLINTERFACE_H
