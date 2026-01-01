/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "viewerplugincreateeventinterface.h"
#include "createeventjob.h"
#include "eventedit.h"
#include <KLocalizedString>

#include <KActionCollection>
#include <QAction>
#include <QIcon>
#include <QLayout>

using namespace MessageViewer;

ViewerPluginCreateEventInterface::ViewerPluginCreateEventInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    createAction(ac);
}

ViewerPluginCreateEventInterface::~ViewerPluginCreateEventInterface() = default;

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginCreateEventInterface::featureTypes() const
{
    return ViewerPluginInterface::NeedMessage;
}

void ViewerPluginCreateEventInterface::setText(const QString &text)
{
    Q_UNUSED(text)
    // Nothing
}

QList<QAction *> ViewerPluginCreateEventInterface::actions() const
{
    return mAction;
}

void ViewerPluginCreateEventInterface::setMessage(const std::shared_ptr<KMime::Message> &value)
{
    widget()->setMessage(value);
}

void ViewerPluginCreateEventInterface::closePlugin()
{
    if (mEventEdit) {
        mEventEdit->slotCloseWidget();
    }
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
        auto act = new QAction(QIcon::fromTheme(QStringLiteral("appointment-new")), i18n("Create Event…"), this);
        act->setIconText(i18n("Create Event"));
        addHelpTextAction(act, i18n("Allows you to create a calendar Event"));
        ac->addAction(QStringLiteral("create_event"), act);
        ac->setDefaultShortcut(act, QKeySequence(Qt::CTRL | Qt::Key_E));
        connect(act, &QAction::triggered, this, &ViewerPluginCreateEventInterface::slotActivatePlugin);
        mAction.append(act);
    }
}

EventEdit *ViewerPluginCreateEventInterface::widget()
{
    if (!mEventEdit) {
        auto parentWidget = static_cast<QWidget *>(parent());
        mEventEdit = new EventEdit(parentWidget);
        connect(mEventEdit, &EventEdit::createEvent, this, &ViewerPluginCreateEventInterface::slotCreateEvent);
        mEventEdit->setObjectName(QLatin1StringView("eventedit"));
        parentWidget->layout()->addWidget(mEventEdit);
        mEventEdit->hide();
    }
    return mEventEdit;
}

void ViewerPluginCreateEventInterface::slotCreateEvent(const KCalendarCore::Event::Ptr &eventPtr, const Akonadi::Collection &collection)
{
    auto createJob = new CreateEventJob(eventPtr, collection, mMessageItem, this);
    createJob->start();
}

#include "moc_viewerplugincreateeventinterface.cpp"
