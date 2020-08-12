/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "zoomtextplugineditorinterface.h"
#include "zoomtexteditorplugin_debug.h"
#include "zoomlabel.h"
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <KActionMenu>

ZoomTextPluginEditorInterface::ZoomTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

ZoomTextPluginEditorInterface::~ZoomTextPluginEditorInterface()
{
}

void ZoomTextPluginEditorInterface::createAction(KActionCollection *ac)
{
    KActionMenu *zoomMenu = new KActionMenu(i18n("Zoom..."), this);
    ac->addAction(QStringLiteral("zoom_menu"), zoomMenu);

    QAction *zoomInAction = KStandardAction::zoomIn(this, &ZoomTextPluginEditorInterface::slotZoomIn, this);
    zoomMenu->addAction(zoomInAction);
    ac->addAction(QStringLiteral("zoom_in"), zoomInAction);

    QAction *zoomOutAction = KStandardAction::zoomOut(this, &ZoomTextPluginEditorInterface::slotZoomOut, this);
    zoomMenu->addAction(zoomOutAction);
    ac->addAction(QStringLiteral("zoom_out"), zoomOutAction);

    zoomMenu->addSeparator();
    QAction *zoomResetAction = KStandardAction::actualSize(this, &ZoomTextPluginEditorInterface::slotZoomReset, this);
    ac->addAction(QStringLiteral("zoom_reset"), zoomResetAction);
    zoomMenu->addAction(zoomResetAction);

    MessageComposer::PluginActionType type(zoomMenu, MessageComposer::PluginActionType::Edit);
    setActionType(type);
    mZoomLabelWidget = new ZoomLabel;
    connect(this, &ZoomTextPluginEditorInterface::zoomFactorChanged, mZoomLabelWidget, &ZoomLabel::setZoomLabel);
    setStatusBarWidget(mZoomLabelWidget);
}

void ZoomTextPluginEditorInterface::slotZoomOut()
{
    mType = ZoomOut;
    Q_EMIT emitPluginActivated(this);
}

void ZoomTextPluginEditorInterface::slotZoomIn()
{
    mType = ZoomIn;
    Q_EMIT emitPluginActivated(this);
}

void ZoomTextPluginEditorInterface::slotZoomReset()
{
    mType = ZoomReset;
    Q_EMIT emitPluginActivated(this);
}

void ZoomTextPluginEditorInterface::exec()
{
    switch (mType) {
    case Unknown:
        qCDebug(KMAIL_EDITOR_ZOOMTEXT_PLUGIN_LOG) << " There is an error here. We can't call this plugin with unknown type";
        break;
    case ZoomReset:
        zoomReset();
        break;
    case ZoomIn:
        zoomIn();
        break;
    case ZoomOut:
        zoomOut();
        break;
    }
    mType = Unknown;
}

void ZoomTextPluginEditorInterface::zoomReset()
{
    richTextEditor()->slotZoomReset();
    Q_EMIT zoomFactorChanged(richTextEditor()->zoomFactor());
}

void ZoomTextPluginEditorInterface::zoomIn()
{
    richTextEditor()->zoomIn();
    Q_EMIT zoomFactorChanged(richTextEditor()->zoomFactor());
}

void ZoomTextPluginEditorInterface::zoomOut()
{
    richTextEditor()->zoomOut();
    Q_EMIT zoomFactorChanged(richTextEditor()->zoomFactor());
}
