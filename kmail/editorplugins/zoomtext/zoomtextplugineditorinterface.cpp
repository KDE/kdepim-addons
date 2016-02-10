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
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <QDebug>

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
#if 0
    PimCommon::KActionMenuZoomText *ZoomTextMenu = new PimCommon::KActionMenuZoomText(this);
    ZoomTextMenu->appendInActionCollection(ac);
    ac->addAction(QStringLiteral("change_case_menu"), ZoomTextMenu);
    connect(ZoomTextMenu, &PimCommon::KActionMenuZoomText::upperCase, this, &ZoomTextPluginEditorInterface::slotUpperCase);
    connect(ZoomTextMenu, &PimCommon::KActionMenuZoomText::lowerCase, this, &ZoomTextPluginEditorInterface::slotLowerCase);
    connect(ZoomTextMenu, &PimCommon::KActionMenuZoomText::sentenceCase, this, &ZoomTextPluginEditorInterface::slotSentenceCase);
    connect(ZoomTextMenu, &PimCommon::KActionMenuZoomText::reverseCase, this, &ZoomTextPluginEditorInterface::slotReverseCase);
    MessageComposer::ActionType type(ZoomTextMenu, MessageComposer::ActionType::Edit);
    setActionType(type);
#endif
}

void ZoomTextPluginEditorInterface::exec()
{
#if 0
    switch(mType) {
    case Unknown:
        qDebug() << " There is an error here. We can't call this plugin with unknown type";
        break;
    case UpperCase:
        upperCase();
        break;
    case LowerCase:
        lowerCase();
        break;
    case SentenseCase:
        sentenceCase();
        break;
    case ReverseCase:
        reverseCase();
        break;
    }
#endif
}


#if 0
void ZoomTextPluginEditorInterface::slotReverseCase()
{
    mType = ReverseCase;
    Q_EMIT emitPluginActivated(this);
}
#endif
