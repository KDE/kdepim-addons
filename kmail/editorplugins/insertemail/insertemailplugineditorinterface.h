/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef INSERTEMAILPLUGINEDITORINTERFACE_H
#define INSERTEMAILPLUGINEDITORINTERFACE_H

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

#endif
