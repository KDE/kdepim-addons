/*
   SPDX-FileCopyrightText: 2019-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <PimCommon/CustomToolsPlugin>
#include <QVariant>
class LanguageToolPlugin : public PimCommon::CustomToolsPlugin
{
    Q_OBJECT
public:
    explicit LanguageToolPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~LanguageToolPlugin() override;

    PimCommon::CustomToolsViewInterface *createView(KActionCollection *ac, PimCommon::CustomToolsWidgetNg *parent) override;
    Q_REQUIRED_RESULT QString customToolName() const override;
    Q_REQUIRED_RESULT bool hasConfigureDialog() const override;
    void showConfigureDialog(QWidget *parent) override;

private:
    Q_DISABLE_COPY(LanguageToolPlugin)
};
