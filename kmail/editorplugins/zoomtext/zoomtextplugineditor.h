/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditor>

#include <MessageComposer/PluginEditorInterface>
#include <QVariant>

class ZoomTextPluginEditor : public MessageComposer::PluginEditor
{
    Q_OBJECT
public:
    explicit ZoomTextPluginEditor(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~ZoomTextPluginEditor() override;

    MessageComposer::PluginEditorInterface *createInterface(QObject *parent = nullptr) override;
    Q_REQUIRED_RESULT bool hasPopupMenuSupport() const override;
    Q_REQUIRED_RESULT bool hasStatusBarSupport() const override;
Q_SIGNALS:
    void zoomFactorChanged(int val);
};
