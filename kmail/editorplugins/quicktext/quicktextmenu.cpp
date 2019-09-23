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
#include <MessageComposer/ConvertSnippetVariablesJob>
#include <QMenu>
#include <QDate>
#include <QTime>
#include <QLocale>

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

    QMenu *toMenuVariable = new QMenu(i18n("To"), mMenu);
    toMenuVariable->addAction(i18n("Emails"), this, &QuickTextMenu::insertToEmails);
    mMenu->addMenu(toMenuVariable);

    QMenu *fromMenuVariable = new QMenu(i18n("From"), mMenu);
    fromMenuVariable->addAction(i18n("Emails"), this, &QuickTextMenu::insertFromEmails);
    mMenu->addMenu(fromMenuVariable);

    QMenu *ccMenuVariable = new QMenu(i18n("Cc"), mMenu);
    ccMenuVariable->addAction(i18n("Emails"), this, &QuickTextMenu::insertCcEmails);
    mMenu->addMenu(ccMenuVariable);

    QMenu *attachmentMenuVariable = new QMenu(i18n("Attachment"), mMenu);
    attachmentMenuVariable->addAction(i18n("Number Of Attachments"), this, &QuickTextMenu::insertNumberOfAttachment);
    attachmentMenuVariable->addAction(i18n("Names"), this, &QuickTextMenu::insertNamesAttachment);
    attachmentMenuVariable->addAction(i18n("Names and Sizes"), this, &QuickTextMenu::insertNamesAndSizesOfAttachment);
    mMenu->addMenu(attachmentMenuVariable);

    QMenu *dateTimeMenuVariable = new QMenu(i18n("Date/Time"), mMenu);
    dateTimeMenuVariable->addAction(i18n("Day Of Week"), this, &QuickTextMenu::insertDayOfWeek);
    dateTimeMenuVariable->addAction(i18n("Date (%1)", QDate::currentDate().toString(Qt::SystemLocaleShortDate)), this, &QuickTextMenu::insertShortDate);
    dateTimeMenuVariable->addAction(i18n("Date (%1)", QDate::currentDate().toString(Qt::SystemLocaleLongDate)), this, &QuickTextMenu::insertLongDate);
    dateTimeMenuVariable->addAction(i18n("Time (%1)", QTime::currentTime().toString(Qt::SystemLocaleShortDate)), this, &QuickTextMenu::insertShortTime);
    dateTimeMenuVariable->addAction(i18n("Time (%1)", QTime::currentTime().toString(Qt::SystemLocaleLongDate)), this, &QuickTextMenu::insertLongTime);
    mMenu->addMenu(dateTimeMenuVariable);

    QMenu *miscVariable = new QMenu(i18n("Misc"), mMenu);
    miscVariable->addAction(i18n("Subject"), this, &QuickTextMenu::insertSubject);
    mMenu->addMenu(miscVariable);
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
    Q_EMIT insertText(mComposerInterface->convertVariable(QStringLiteral("%ATTACHMENTCOUNT")));
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

void QuickTextMenu::insertCcEmails()
{
    Q_EMIT insertText(mComposerInterface->cc());
}

void QuickTextMenu::insertFromEmails()
{
    Q_EMIT insertText(mComposerInterface->from());
}

void QuickTextMenu::insertSubject()
{
    Q_EMIT insertText(mComposerInterface->subject());
}

void QuickTextMenu::insertShortDate()
{
    Q_EMIT insertText(mComposerInterface->shortDate());
}

void QuickTextMenu::insertLongDate()
{
    Q_EMIT insertText(mComposerInterface->longDate());
}

void QuickTextMenu::insertShortTime()
{
    Q_EMIT insertText(mComposerInterface->shortTime());
}

void QuickTextMenu::insertLongTime()
{
    Q_EMIT insertText(mComposerInterface->longTime());
}

void QuickTextMenu::insertDayOfWeek()
{
    Q_EMIT insertText(mComposerInterface->insertDayOfWeek());
}
