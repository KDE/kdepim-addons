/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/HeaderStylePlugin>

#include <QVariant>

namespace MessageViewer
{
class GrantleeHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit GrantleeHeaderStylePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~GrantleeHeaderStylePlugin() override;

    [[nodiscard]] HeaderStyle *headerStyle() const override;
    [[nodiscard]] HeaderStrategy *headerStrategy() const override;
    [[nodiscard]] HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    [[nodiscard]] QString name() const override;

private:
    HeaderStyle *const mHeaderStyle;
    HeaderStrategy *const mHeaderStrategy;
};
}
