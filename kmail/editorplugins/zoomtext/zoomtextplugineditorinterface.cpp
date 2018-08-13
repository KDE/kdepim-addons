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

#include "zoomtextplugineditorinterface.h"
#include "zoomtexteditorplugin_debug.h"
#include "zoomlabel.h"
#include <kconfig_version.h>
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
#if KCONFIG_VERSION < QT_VERSION_CHECK(5, 50, 0)
    QAction *zoomResetAction = new QAction(i18n("Reset"), this);
    zoomMenu->addAction(zoomResetAction);
    ac->addAction(QStringLiteral("zoom_reset"), zoomResetAction);
    connect(zoomResetAction, &QAction::triggered, this, &ZoomTextPluginEditorInterface::slotZoomReset);
    ac->setDefaultShortcut(zoomResetAction, QKeySequence(Qt::CTRL + Qt::Key_0));
#else
    QAction *zoomResetAction = KStandardAction::actualSize(this, &ZoomTextPluginEditorInterface::slotZoomReset, this);
    ac->addAction(QStringLiteral("zoom_reset"), zoomResetAction);
    zoomMenu->addAction(zoomResetAction);
#endif


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
