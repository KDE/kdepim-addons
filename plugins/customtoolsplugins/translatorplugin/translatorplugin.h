/*
   SPDX-FileCopyrightText: 2015-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <PimCommon/CustomToolsPlugin>

#include <QVariant>
class TranslatorPlugin : public PimCommon::CustomToolsPlugin
{
    Q_OBJECT
public:
    explicit TranslatorPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~TranslatorPlugin() override;

    [[nodiscard]] PimCommon::CustomToolsViewInterface *createView(KActionCollection *ac, PimCommon::CustomToolsWidgetNg *parent) override;
    [[nodiscard]] QString customToolName() const override;
    [[nodiscard]] bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent) override;
};
