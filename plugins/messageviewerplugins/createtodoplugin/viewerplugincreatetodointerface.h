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

#ifndef VIEWERPLUGINCREATETODOINTERFACE_H
#define VIEWERPLUGINCREATETODOINTERFACE_H

#include <messageviewer/viewerplugininterface.h>
#include <KCalCore/Todo>
#include <AkonadiCore/Collection>
class KActionCollection;
namespace MessageViewer {
class TodoEdit;
class ViewerPluginCreateTodoInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginCreateTodoInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginCreateTodoInterface();

    void setText(const QString &text) override;
    QList<QAction *> actions() const override;
    void setMessage(const KMime::Message::Ptr &value) override;
    void closePlugin() override;
    void showWidget() override;
    void setMessageItem(const Akonadi::Item &item) override;
    ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;
    void setCurrentCollection(const Akonadi::Collection &col) override;

private:
    void slotCreateTodo(const KCalCore::Todo::Ptr &todoPtr, const Akonadi::Collection &collection);
    void createAction(KActionCollection *ac);
    TodoEdit *widget();

    TodoEdit *mTodoEdit = nullptr;
    QList<QAction *> mAction;
    Akonadi::Item mMessageItem;
};
}
#endif // VIEWERPLUGINCREATETODOINTERFACE_H
