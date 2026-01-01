/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "zoomtextplugineditorinterface.h"
using namespace Qt::Literals::StringLiterals;

#include "zoomlabel.h"
#include "zoomtexteditorplugin_debug.h"
#include <KActionCollection>
#include <KActionMenu>
#include <KLocalizedString>
#include <QAction>
#include <TextCustomEditor/RichTextEditor>

ZoomTextPluginEditorInterface::ZoomTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
}

ZoomTextPluginEditorInterface::~ZoomTextPluginEditorInterface() = default;

void ZoomTextPluginEditorInterface::createAction(KActionCollection *ac)
{
    auto zoomMenu = new KActionMenu(i18n("Zoom…"), this);
    ac->addAction(u"zoom_menu"_s, zoomMenu);

    QAction *zoomInAction = KStandardActions::zoomIn(this, &ZoomTextPluginEditorInterface::slotZoomIn, this);
    zoomMenu->addAction(zoomInAction);
    ac->addAction(u"zoom_in"_s, zoomInAction);

    QAction *zoomOutAction = KStandardActions::zoomOut(this, &ZoomTextPluginEditorInterface::slotZoomOut, this);
    zoomMenu->addAction(zoomOutAction);
    ac->addAction(u"zoom_out"_s, zoomOutAction);

    zoomMenu->addSeparator();
    QAction *zoomResetAction = KStandardActions::actualSize(this, &ZoomTextPluginEditorInterface::slotZoomReset, this);
    ac->addAction(u"zoom_reset"_s, zoomResetAction);
    zoomMenu->addAction(zoomResetAction);

    MessageComposer::PluginActionType type(zoomMenu, MessageComposer::PluginActionType::View);
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

#include "moc_zoomtextplugineditorinterface.cpp"
