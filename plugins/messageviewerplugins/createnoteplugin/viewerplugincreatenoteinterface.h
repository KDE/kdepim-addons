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

#ifndef VIEWERPLUGINCREATENOTEINTERFACE_H
#define VIEWERPLUGINCREATENOTEINTERFACE_H

#include <messageviewer/viewerplugininterface.h>
class KActionCollection;

namespace MessageViewer {
class NoteEdit;
class ViewerPluginCreatenoteInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginCreatenoteInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginCreatenoteInterface();

    void setText(const QString &text) override;
    QList<QAction *> actions() const override;
    void setMessage(const KMime::Message::Ptr &value) override;
    void closePlugin() override;
    void showWidget() override;
    void setMessageItem(const Akonadi::Item &item) override;
    void updateAction(const Akonadi::Item &item) override;
    ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;

private:
    void slotCreateNote(const KMime::Message::Ptr &notePtr, const Akonadi::Collection &collection);

    void slotNoteItemFetched(KJob *job);
    Akonadi::Relation relatedNoteRelation() const;
    void showCreateNewNoteWidget();
    void createAction(KActionCollection *ac);
    NoteEdit *widget();

    Akonadi::Item mMessageItem;
    NoteEdit *mNoteEdit;
    QList<QAction *> mAction;
};
}
#endif // VIEWERPLUGINCREATENOTEINTERFACE_H
