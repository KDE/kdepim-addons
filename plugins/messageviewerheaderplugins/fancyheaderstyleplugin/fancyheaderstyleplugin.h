/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageViewer/HeaderStylePlugin>

#include <QVariant>

namespace MessageViewer
{
class FancyHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit FancyHeaderStylePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~FancyHeaderStylePlugin() override;

    [[nodiscard]] HeaderStyle *headerStyle() const override;
    [[nodiscard]] HeaderStrategy *headerStrategy() const override;
    [[nodiscard]] HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    [[nodiscard]] QString name() const override;
    [[nodiscard]] int elidedTextSize() const override;
    [[nodiscard]] QString extraScreenCss(const QString &headerFont) const override;
    [[nodiscard]] QString extraPrintCss(const QString &headerFont) const override;
    [[nodiscard]] QString extraCommonCss(const QString &headerFont) const override;
    [[nodiscard]] QString attachmentHtml() const override;

private:
    HeaderStyle *const mHeaderStyle;
    HeaderStrategy *const mHeaderStrategy;
};
}
