/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Collection>
#include <KCalendarCore/Todo>
#include <MessageViewer/ViewerPluginInterface>
class KActionCollection;
namespace MessageViewer
{
class TodoEdit;
class ViewerPluginCreateTodoInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginCreateTodoInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginCreateTodoInterface() override;

    void setText(const QString &text) override;
    [[nodiscard]] QList<QAction *> actions() const override;
    void setMessage(const std::shared_ptr<KMime::Message> &value) override;
    void closePlugin() override;
    void showWidget() override;
    void setMessageItem(const Akonadi::Item &item) override;
    [[nodiscard]] ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;
    void setCurrentCollection(const Akonadi::Collection &col) override;

private:
    void slotCreateTodo(const KCalendarCore::Todo::Ptr &todoPtr, const Akonadi::Collection &collection);
    void createAction(KActionCollection *ac);
    [[nodiscard]] TodoEdit *widget();

    TodoEdit *mTodoEdit = nullptr;
    QList<QAction *> mAction;
    Akonadi::Item mMessageItem;
};
}
