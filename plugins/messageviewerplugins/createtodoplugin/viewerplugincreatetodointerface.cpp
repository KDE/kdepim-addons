/*
   Copyright (C) 2015-2018 Montel Laurent <montel@kde.org>

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

#include "viewerplugincreatetodointerface.h"
#include "todoedit.h"
#include "createtodojob.h"

#include <KLocalizedString>

#include <KActionCollection>
#include <QAction>
#include <QLayout>

using namespace MessageViewer;

ViewerPluginCreateTodoInterface::ViewerPluginCreateTodoInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    createAction(ac);
}

ViewerPluginCreateTodoInterface::~ViewerPluginCreateTodoInterface()
{
}

void ViewerPluginCreateTodoInterface::setText(const QString &text)
{
    Q_UNUSED(text);
    //Nothing
}

QList<QAction *> ViewerPluginCreateTodoInterface::actions() const
{
    return mAction;
}

void ViewerPluginCreateTodoInterface::setMessage(const KMime::Message::Ptr &value)
{
    widget()->setMessage(value);
}

void ViewerPluginCreateTodoInterface::closePlugin()
{
    if (mTodoEdit) {
        mTodoEdit->slotCloseWidget();
    }
}

void ViewerPluginCreateTodoInterface::showWidget()
{
    widget()->showToDoWidget();
}

void ViewerPluginCreateTodoInterface::setMessageItem(const Akonadi::Item &item)
{
    mMessageItem = item;
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginCreateTodoInterface::featureTypes() const
{
    return ViewerPluginInterface::NeedMessage;
}

void ViewerPluginCreateTodoInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        QAction *act = new QAction(QIcon::fromTheme(QStringLiteral("task-new")), i18n("Create Todo"), this);
        act->setIconText(i18n("Create To-do"));
        addHelpTextAction(act, i18n("Allows you to create a calendar to-do or reminder from this message"));
        act->setWhatsThis(i18n(
                              "This option starts the KOrganizer to-do editor with initial values taken from the currently selected message. Then you can edit the to-do to your liking before saving it to your calendar."));
        ac->addAction(QStringLiteral("create_todo"), act);
        ac->setDefaultShortcut(act, QKeySequence(Qt::CTRL + Qt::Key_T));
        connect(act, &QAction::triggered, this, &ViewerPluginCreateTodoInterface::slotActivatePlugin);
        mAction.append(act);
    }
}

void ViewerPluginCreateTodoInterface::slotCreateTodo(const KCalCore::Todo::Ptr &todoPtr, const Akonadi::Collection &collection)
{
    CreateTodoJob *createJob = new CreateTodoJob(todoPtr, collection, mMessageItem, this);
    createJob->start();
}

TodoEdit *ViewerPluginCreateTodoInterface::widget()
{
    if (!mTodoEdit) {
        QWidget *parentWidget = static_cast<QWidget *>(parent());
        mTodoEdit = new TodoEdit(parentWidget);
        connect(mTodoEdit, &TodoEdit::createTodo, this, &ViewerPluginCreateTodoInterface::slotCreateTodo);
        mTodoEdit->setObjectName(QStringLiteral("todoedit"));
        parentWidget->layout()->addWidget(mTodoEdit);
        mTodoEdit->hide();
    }
    return mTodoEdit;
}

void MessageViewer::ViewerPluginCreateTodoInterface::setCurrentCollection(const Akonadi::Collection &col)
{
    widget()->setCurrentCollection(col);
}
