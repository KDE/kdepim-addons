/*
   SPDX-FileCopyrightText: 2018-2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <PimCommon/PurposeMenuWidget>
class ShareTextPluginEditorInterface;
class SharetextPurposeMenuWidget : public PimCommon::PurposeMenuWidget
{
    Q_OBJECT
public:
    explicit SharetextPurposeMenuWidget(QWidget *parentWidget, QObject *parent = nullptr);
    ~SharetextPurposeMenuWidget() override;

    Q_REQUIRED_RESULT QByteArray text() override;
    void setEditorWidget(ShareTextPluginEditorInterface *interface);

private:
    ShareTextPluginEditorInterface *mInterface = nullptr;
};

