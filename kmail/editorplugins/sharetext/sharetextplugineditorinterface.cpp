/*
   SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "sharetextplugineditorinterface.h"
#include "sharetexteditorplugin_debug.h"
#include "sharetextpurposemenuwidget.h"
#include <KActionCollection>
#include <KActionMenu>
#include <KLocalizedString>
#include <PimCommon/KActionMenuChangeCase>
#include <TextCustomEditor/RichTextEditor>

#include <QAction>
#include <QMenu>

ShareTextPluginEditorInterface::ShareTextPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
    setNeedSelectedText(false);
}

ShareTextPluginEditorInterface::~ShareTextPluginEditorInterface() = default;

void ShareTextPluginEditorInterface::createAction(KActionCollection *ac)
{
    auto purposeMenu = new SharetextPurposeMenuWidget(parentWidget(), this);
    connect(purposeMenu, &SharetextPurposeMenuWidget::shareError, this, &ShareTextPluginEditorInterface::errorMessage);
    connect(purposeMenu, &SharetextPurposeMenuWidget::shareSuccess, this, &ShareTextPluginEditorInterface::successMessage);

    auto shareAction = new KActionMenu(i18n("Share Mail Text..."), this);
    shareAction->setMenu(purposeMenu->menu());
    shareAction->setIcon(QIcon::fromTheme(QStringLiteral("document-share")));
    shareAction->setPopupMode(QToolButton::InstantPopup);
    ac->addAction(QStringLiteral("share_text_menu"), shareAction);
    purposeMenu->setEditorWidget(this);
    MessageComposer::PluginActionType type(shareAction, MessageComposer::PluginActionType::File);
    setActionType(type);
}

void ShareTextPluginEditorInterface::exec()
{
    // Nothing
}

#include "moc_sharetextplugineditorinterface.cpp"
