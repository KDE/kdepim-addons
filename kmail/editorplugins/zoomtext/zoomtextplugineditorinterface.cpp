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

#include "zoomtextplugineditorinterface.h"
#include "zoomtexteditorplugin_debug.h"
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <KActionMenu>

ZoomTextPluginEditorInterface::ZoomTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent),
      mType(Unknown)
{

}

ZoomTextPluginEditorInterface::~ZoomTextPluginEditorInterface()
{

}

bool ZoomTextPluginEditorInterface::hasPopupMenuSupport() const
{
    return false;
}

void ZoomTextPluginEditorInterface::createAction(KActionCollection *ac)
{
    KActionMenu *zoomMenu = new KActionMenu(i18n("Zoom..."), this);
    ac->addAction(QStringLiteral("zoom_menu"), zoomMenu);

    QAction *zoomInAction = new QAction(QIcon::fromTheme(QStringLiteral("zoom-in")), i18n("&Zoom In"), this);
    zoomMenu->addAction(zoomInAction);
    ac->addAction(QStringLiteral("zoom_in"), zoomInAction);
    connect(zoomInAction, &QAction::triggered, this, &ZoomTextPluginEditorInterface::slotZoomIn);
    ac->setDefaultShortcut(zoomInAction, QKeySequence(Qt::CTRL | Qt::Key_Plus));

    QAction *zoomOutAction = new QAction(QIcon::fromTheme(QStringLiteral("zoom-out")), i18n("Zoom &Out"), this);
    zoomMenu->addAction(zoomOutAction);
    ac->addAction(QStringLiteral("zoom_out"), zoomOutAction);
    connect(zoomOutAction, &QAction::triggered, this, &ZoomTextPluginEditorInterface::slotZoomOut);
    ac->setDefaultShortcut(zoomOutAction, QKeySequence(Qt::CTRL | Qt::Key_Minus));

    zoomMenu->addSeparator();
    QAction *zoomResetAction = new QAction(i18n("Reset"), this);
    zoomMenu->addAction(zoomResetAction);
    ac->addAction(QStringLiteral("zoom_reset"), zoomResetAction);
    connect(zoomResetAction, &QAction::triggered, this, &ZoomTextPluginEditorInterface::slotZoomReset);
    ac->setDefaultShortcut(zoomResetAction, QKeySequence(Qt::CTRL | Qt::Key_0));

    MessageComposer::ActionType type(zoomMenu, MessageComposer::ActionType::Edit);
    setActionType(type);
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
}

void ZoomTextPluginEditorInterface::zoomIn()
{
    richTextEditor()->zoomIn();
}

void ZoomTextPluginEditorInterface::zoomOut()
{
    richTextEditor()->zoomOut();
}
