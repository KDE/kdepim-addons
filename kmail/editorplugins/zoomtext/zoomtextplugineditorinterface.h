/*
   Copyright (C) 2016-2017 Montel Laurent <montel@kde.org>

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

#ifndef ZOOMTEXTPLUGINEDITORINTERFACE_H
#define ZOOMTEXTPLUGINEDITORINTERFACE_H

#include <messagecomposer/plugineditorinterface.h>

class ZoomTextPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit ZoomTextPluginEditorInterface(QObject *parent = Q_NULLPTR);
    ~ZoomTextPluginEditorInterface();

    void createAction(KActionCollection *ac) Q_DECL_OVERRIDE;
    void exec() Q_DECL_OVERRIDE;

private:
    void slotZoomOut();
    void slotZoomIn();
    void slotZoomReset();

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
