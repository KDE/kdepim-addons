/*
   Copyright (C) 2015-2017 Montel Laurent <montel@kde.org>

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

#ifndef VIEWERPLUGINCREATEEVENTINTERFACE_H
#define VIEWERPLUGINCREATEEVENTINTERFACE_H

#include <messageviewer/viewerplugininterface.h>
#include <KCalCore/Event>
class KActionCollection;
namespace MessageViewer {
class EventEdit;
class ViewerPluginCreateEventInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginCreateEventInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginCreateEventInterface();

    void setText(const QString &text) override;
    QList<QAction *> actions() const override;
    void setMessage(const KMime::Message::Ptr &value) override;
    void closePlugin() override;
    void showWidget() override;
    void setMessageItem(const Akonadi::Item &item) override;
    ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;

private Q_SLOTS:
    void slotCreateEvent(const KCalCore::Event::Ptr &eventPtr, const Akonadi::Collection &collection);

private:
    void createAction(KActionCollection *ac);
    EventEdit *widget();

    Akonadi::Item mMessageItem;
    EventEdit *mEventEdit = nullptr;
    QList<QAction *> mAction;
};
}
#endif // VIEWERPLUGINCREATEEVENTINTERFACE_H
