/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/ViewerPluginInterface>
class KActionCollection;
class ViewerPluginAIWidget;
namespace MessageViewer
{
class ViewerPluginAIInterface : public ViewerPluginInterface
{
    Q_OBJECT
public:
    explicit ViewerPluginAIInterface(KActionCollection *ac, QWidget *parent = nullptr);
    ~ViewerPluginAIInterface() override;

    void setText(const QString &text) override;
    [[nodiscard]] QList<QAction *> actions() const override;
    void showWidget() override;
    [[nodiscard]] ViewerPluginInterface::SpecificFeatureTypes featureTypes() const override;

private:
    [[nodiscard]] ViewerPluginAIWidget *widget();
    void createAction(KActionCollection *ac);
    QList<QAction *> mAction;
    ViewerPluginAIWidget *mAiWidget = nullptr;
};
}
