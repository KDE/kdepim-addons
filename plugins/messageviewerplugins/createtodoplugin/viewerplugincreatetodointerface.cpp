/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreatetodointerface.h"
#include "createtodojob.h"
#include "todoedit.h"

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

ViewerPluginCreateTodoInterface::~ViewerPluginCreateTodoInterface() = default;

void ViewerPluginCreateTodoInterface::setText(const QString &text)
{
    Q_UNUSED(text)
    // Nothing
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
        auto act = new QAction(QIcon::fromTheme(QStringLiteral("task-new")), i18n("Create To-do"), this);
        act->setIconText(i18n("Create To-do"));
        addHelpTextAction(act, i18n("Allows you to create a calendar to-do or reminder from this message"));
        act->setWhatsThis(
            i18n("This option starts the KOrganizer to-do editor with initial values taken from the currently selected message. Then you can edit the to-do to "
                 "your liking before saving it to your calendar."));
        ac->addAction(QStringLiteral("create_todo"), act);
        ac->setDefaultShortcut(act, QKeySequence(Qt::CTRL | Qt::Key_T));
        connect(act, &QAction::triggered, this, &ViewerPluginCreateTodoInterface::slotActivatePlugin);
        mAction.append(act);
    }
}

void ViewerPluginCreateTodoInterface::slotCreateTodo(const KCalendarCore::Todo::Ptr &todoPtr, const Akonadi::Collection &collection)
{
    auto createJob = new CreateTodoJob(todoPtr, collection, mMessageItem, this);
    createJob->start();
}

TodoEdit *ViewerPluginCreateTodoInterface::widget()
{
    if (!mTodoEdit) {
        auto parentWidget = static_cast<QWidget *>(parent());
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

#include "moc_viewerplugincreatetodointerface.cpp"
