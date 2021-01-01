/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef SHARETEXTPURPOSEMENUWIDGET_H
#define SHARETEXTPURPOSEMENUWIDGET_H

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

#endif // SHARETEXTPURPOSEMENUWIDGET_H
