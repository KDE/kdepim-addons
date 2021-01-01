/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TRANSLATORPLUGIN_H
#define TRANSLATORPLUGIN_H
#include <PimCommon/CustomToolsPlugin>

#include <QVariant>
class TranslatorPlugin : public PimCommon::CustomToolsPlugin
{
    Q_OBJECT
public:
    explicit TranslatorPlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~TranslatorPlugin() override;

    PimCommon::CustomToolsViewInterface *createView(KActionCollection *ac, PimCommon::CustomToolsWidgetNg *parent) override;
    QString customToolName() const override;
};
#endif // TRANSLATORPLUGIN_H
