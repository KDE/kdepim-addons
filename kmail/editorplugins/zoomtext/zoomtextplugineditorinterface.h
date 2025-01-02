/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>
class ZoomLabel;
class ZoomTextPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit ZoomTextPluginEditorInterface(QObject *parent = nullptr);
    ~ZoomTextPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

Q_SIGNALS:
    void zoomFactorChanged(int val);

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
        ZoomOut,
    };
    ZoomTextType mType = Unknown;
    ZoomLabel *mZoomLabelWidget = nullptr;
};
