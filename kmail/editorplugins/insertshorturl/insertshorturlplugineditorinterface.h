/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MessageComposer/PluginEditorInterface>
#include <QHash>
class ShortUrlEngineInterface;
class InsertShorturlPluginEditorInterface : public MessageComposer::PluginEditorInterface
{
    Q_OBJECT
public:
    explicit InsertShorturlPluginEditorInterface(QObject *parent = nullptr);
    ~InsertShorturlPluginEditorInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;

    void loadEngine();

private:
    void initializePlugins();
    void slotActivated();
    void slotShortUrlFailed(const QString &errMsg);
    QHash<QString, ShortUrlEngineInterface *> mLstInterface;
    ShortUrlEngineInterface *mCurrentEngine = nullptr;
};
