/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>
#include <QPointer>
class SelectMailDialog;
class InsertEmailPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit InsertEmailPluginEditorInterface(QObject *parent = nullptr);
    ~InsertEmailPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

private:
    void slotEmailSelected(const QStringList &lst);
    void slotActivated();
    QPointer<SelectMailDialog> mSelectMailDialog;
};
