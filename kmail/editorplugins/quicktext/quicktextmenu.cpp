/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#include "quicktextmenu.h"
#include <KLocalizedString>
#include <MessageComposer/PluginComposerInterface>
#include <QMenu>

QuickTextMenu::QuickTextMenu(QWidget *parentWidget, QObject *parent)
    : QObject(parent)
    , mParentWidget(parentWidget)
{
    initializeMenu();
}

QuickTextMenu::~QuickTextMenu()
{
}

void QuickTextMenu::initializeMenu()
{
    mMenu = new QMenu(mParentWidget);
    mMenu->setFocusPolicy(Qt::NoFocus);

    QMenu *toMenuVariable = new QMenu(i18n("To:"), mMenu);
    toMenuVariable->addAction(i18n("Emails"), this, &QuickTextMenu::insertToEmails);
    mMenu->addMenu(toMenuVariable);

    QMenu *attachmentMenuVariable = new QMenu(i18n("Attachment"), mMenu);
    attachmentMenuVariable->addAction(i18n("Number Of Attachments"), this, &QuickTextMenu::insertNumberOfAttachment);
    attachmentMenuVariable->addAction(i18n("Names"), this, &QuickTextMenu::insertNamesAttachment);
    attachmentMenuVariable->addAction(i18n("Names and Sizes"), this, &QuickTextMenu::insertNamesAndSizesOfAttachment);
    mMenu->addMenu(attachmentMenuVariable);
}

QMenu *QuickTextMenu::menu() const
{
    return mMenu;
}

void QuickTextMenu::setPluginComposerInterface(MessageComposer::PluginComposerInterface *composerInterface)
{
    mComposerInterface = composerInterface;
}

void QuickTextMenu::insertNumberOfAttachment()
{
    Q_EMIT insertText(QString::number(mComposerInterface->attachments().count()));
}

void QuickTextMenu::insertNamesAttachment()
{
    Q_EMIT insertText(mComposerInterface->attachments().names().join(QLatin1String(", ")));
}

void QuickTextMenu::insertNamesAndSizesOfAttachment()
{
    Q_EMIT insertText(mComposerInterface->attachments().namesAndSize().join(QLatin1String(", ")));
}

void QuickTextMenu::insertToEmails()
{
    Q_EMIT insertText(mComposerInterface->to());
}
