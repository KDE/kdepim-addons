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

#ifndef ZOOMTEXTPLUGINEDITORINTERFACE_H
#define ZOOMTEXTPLUGINEDITORINTERFACE_H

#include <messagecomposer/plugineditorinterface.h>
#include <QPointer>

class ZoomTextPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit ZoomTextPluginEditorInterface(QObject *parent = Q_NULLPTR);
    ~ZoomTextPluginEditorInterface();

    void createAction(KActionCollection *ac) Q_DECL_OVERRIDE;
    void exec() Q_DECL_OVERRIDE;
    bool hasPopupMenuSupport() const Q_DECL_OVERRIDE;

private Q_SLOTS:
    void slotZoomOut();

    void slotZoomIn();
    void slotZoomReset();
private:
    void zoomReset();
    void zoomIn();
    void zoomOut();
    enum ZoomTextType {
        Unknown = -1,
        ZoomReset = 0,
        ZoomIn,
        ZoomOut
    };
    ZoomTextType mType;
};

#endif
