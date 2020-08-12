/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINCREATENOTEINTERFACE_H
#define VIEWERPLUGINCREATENOTEINTERFACE_H

#include <MessageViewer/ViewerPluginInterface>
class KActionCollection;

namespace MessageViewer {
class NoteEdit;
class ViewerPluginCreatenoteInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginCreatenoteInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginCreatenoteInterface() override;

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
    NoteEdit *mNoteEdit = nullptr;
    QList<QAction *> mAction;
};
}
#endif // VIEWERPLUGINCREATENOTEINTERFACE_H
