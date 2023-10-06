/*
   SPDX-FileCopyrightText: 2019-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/CustomToolsPlugin>
#include <QVariant>
class GrammalectePlugin : public PimCommon::CustomToolsPlugin
{
    Q_OBJECT
public:
    explicit GrammalectePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~GrammalectePlugin() override;

    PimCommon::CustomToolsViewInterface *createView(KActionCollection *ac, PimCommon::CustomToolsWidgetNg *parent) override;
    [[nodiscard]] QString customToolName() const override;
    [[nodiscard]] bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent) override;

private:
    Q_DISABLE_COPY(GrammalectePlugin)
};
