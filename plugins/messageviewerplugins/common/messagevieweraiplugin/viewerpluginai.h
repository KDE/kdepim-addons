/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/ViewerPlugin>
#include <QVariant>
namespace MessageViewer
{
class ViewerPluginAI : public MessageViewer::ViewerPlugin
{
    Q_OBJECT
public:
    explicit ViewerPluginAI(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());

    [[nodiscard]] ViewerPluginInterface *createView(QWidget *parent, KActionCollection *ac) override;
    [[nodiscard]] QString viewerPluginName() const override;

    void showConfigureDialog(QWidget *parent) override;
    [[nodiscard]] bool hasConfigureDialog() const override;
};
}
