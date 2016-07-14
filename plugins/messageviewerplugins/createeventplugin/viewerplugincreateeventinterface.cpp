/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

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

#include "viewerplugincreateeventinterface.h"
#include "eventedit.h"
#include "createeventjob.h"
#include <KLocalizedString>

#include <KActionCollection>
#include <QHBoxLayout>
#include <QIcon>
#include <QAction>

using namespace MessageViewer;

ViewerPluginCreateEventInterface::ViewerPluginCreateEventInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent),
      mEventEdit(Q_NULLPTR)
{
    createAction(ac);
}

ViewerPluginCreateEventInterface::~ViewerPluginCreateEventInterface()
{

}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginCreateEventInterface::featureTypes() const
{
    return ViewerPluginInterface::NeedMessage;
}

void ViewerPluginCreateEventInterface::setText(const QString &text)
{
    Q_UNUSED(text);
    //Nothing
}

QList<QAction *> ViewerPluginCreateEventInterface::actions() const
{
    return mAction;
}

void ViewerPluginCreateEventInterface::setMessage(const KMime::Message::Ptr &value)
{
    widget()->setMessage(value);
}

void ViewerPluginCreateEventInterface::closePlugin()
{
    widget()->slotCloseWidget();
}

void ViewerPluginCreateEventInterface::showWidget()
{
    widget()->showEventEdit();
}

void ViewerPluginCreateEventInterface::setMessageItem(const Akonadi::Item &item)
{
    mMessageItem = item;
}

void ViewerPluginCreateEventInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        QAction *act = new QAction(QIcon::fromTheme(QStringLiteral("appointment-new")), i18n("Create Event..."), this);
        act->setIconText(i18n("Create Event"));
        addHelpTextAction(act, i18n("Allows you to create a calendar Event"));
        ac->addAction(QStringLiteral("create_event"), act);
        ac->setDefaultShortcut(act, QKeySequence(Qt::CTRL + Qt::Key_E));
        connect(act, &QAction::triggered, this, &ViewerPluginCreateEventInterface::slotActivatePlugin);
        mAction.append(act);
    }
}

EventEdit *ViewerPluginCreateEventInterface::widget()
{
    if (!mEventEdit) {
        QWidget *parentWidget = static_cast<QWidget *>(parent());
        mEventEdit = new EventEdit(parentWidget);
        connect(mEventEdit, &EventEdit::createEvent, this, &ViewerPluginCreateEventInterface::slotCreateEvent);
        mEventEdit->setObjectName(QStringLiteral("eventedit"));
        parentWidget->layout()->addWidget(mEventEdit);
        mEventEdit->hide();
    }
    return mEventEdit;
}

void ViewerPluginCreateEventInterface::slotCreateEvent(const KCalCore::Event::Ptr &eventPtr, const Akonadi::Collection &collection)
{
    CreateEventJob *createJob = new CreateEventJob(eventPtr, collection, mMessageItem, this);
    createJob->start();
}
