/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

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

    HeaderStyle *headerStyle() const override;
    HeaderStrategy *headerStrategy() const override;
    HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    Q_REQUIRED_RESULT QString name() const override;
    Q_REQUIRED_RESULT int elidedTextSize() const override;
    Q_REQUIRED_RESULT QString extraScreenCss(const QString &headerFont) const override;
    Q_REQUIRED_RESULT QString extraPrintCss(const QString &headerFont) const override;
    Q_REQUIRED_RESULT QString extraCommonCss(const QString &headerFont) const override;
    Q_REQUIRED_RESULT QString attachmentHtml() const override;

private:
    HeaderStyle *const mHeaderStyle;
    HeaderStrategy *const mHeaderStrategy;
};
}
