/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KCalendarCore/Event>
#include <MessageViewer/ViewerPluginInterface>
class KActionCollection;
namespace MessageViewer
{
class EventEdit;
class ViewerPluginCreateEventInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginCreateEventInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginCreateEventInterface() override;

    void setText(const QString &text) override;
    Q_REQUIRED_RESULT QList<QAction *> actions() const override;
    void setMessage(const KMime::Message::Ptr &value) override;
    void closePlugin() override;
    void showWidget() override;
    void setMessageItem(const Akonadi::Item &item) override;
    Q_REQUIRED_RESULT ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;

private:
    void slotCreateEvent(const KCalendarCore::Event::Ptr &eventPtr, const Akonadi::Collection &collection);
    void createAction(KActionCollection *ac);
    EventEdit *widget();

    Akonadi::Item mMessageItem;
    EventEdit *mEventEdit = nullptr;
    QList<QAction *> mAction;
};
}
