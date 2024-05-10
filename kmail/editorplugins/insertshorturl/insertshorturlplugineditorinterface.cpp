/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "insertshorturlplugineditorinterface.h"
#include "kmail_insertshorturl_debug.h"
#include "shorturlengineplugin/shorturlengineinterface.h"
#include "shorturlengineplugin/shorturlengineplugin.h"
#include "shorturlengineplugin/shorturlenginepluginmanager.h"
#include <KActionCollection>
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <PimCommon/NetworkManager>
#include <QAction>
#include <TextCustomEditor/RichTextEditor>

InsertShorturlPluginEditorInterface::InsertShorturlPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
    setNeedSelectedText(true);
    initializePlugins();
    loadEngine();
}

InsertShorturlPluginEditorInterface::~InsertShorturlPluginEditorInterface() = default;

void InsertShorturlPluginEditorInterface::initializePlugins()
{
    const QList<ShortUrlEnginePlugin *> lstPlugin = ShortUrlEnginePluginManager::self()->pluginsList();
    for (ShortUrlEnginePlugin *plugin : lstPlugin) {
        ShortUrlEngineInterface *interface = plugin->createInterface(this);
        if (interface) {
            mLstInterface.insert(interface->engineName(), interface);
        }
    }
}

void InsertShorturlPluginEditorInterface::loadEngine()
{
    if (mCurrentEngine) {
        disconnect(mCurrentEngine, &ShortUrlEngineInterface::shortUrlFailed, this, &InsertShorturlPluginEditorInterface::slotShortUrlFailed);
    }

    KConfigGroup grp(KSharedConfig::openConfig(), QStringLiteral("ShortUrl"));
    const QString engineName = grp.readEntry("EngineName");
    mCurrentEngine = mLstInterface.value(engineName);
    if (!mCurrentEngine && !mLstInterface.isEmpty()) {
        mCurrentEngine = mLstInterface.cbegin().value();
    }

    if (mCurrentEngine) {
        connect(mCurrentEngine, &ShortUrlEngineInterface::shortUrlFailed, this, &InsertShorturlPluginEditorInterface::slotShortUrlFailed);
    }
}

void InsertShorturlPluginEditorInterface::createAction(KActionCollection *ac)
{
    auto action = new QAction(i18n("Insert Short URL…"), this);
    ac->addAction(QStringLiteral("insert_shortulr"), action);
    connect(action, &QAction::triggered, this, &InsertShorturlPluginEditorInterface::slotActivated);
    MessageComposer::PluginActionType type(action, MessageComposer::PluginActionType::PopupMenu);
    setActionType(type);
}

void InsertShorturlPluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void InsertShorturlPluginEditorInterface::exec()
{
    QTextCursor textCursor = richTextEditor()->textCursor();
    const QString urlStr = textCursor.selectedText();

    if (urlStr.startsWith(QLatin1StringView("http:")) || urlStr.startsWith(QLatin1StringView("https:")) || urlStr.startsWith(QLatin1StringView("ftp:"))
        || urlStr.startsWith(QLatin1StringView("ftps:"))) {
        if (!mCurrentEngine) {
            qCWarning(KMAIL_INSERTSHORTURL_LOG) << "Current Engine not defined";
            return;
        }
        if (!PimCommon::NetworkManager::self()->isOnline()) {
            Q_EMIT message(i18n("No network connection detected, we cannot shorten URL."));
            return;
        }
        mCurrentEngine->setTextCursor(textCursor);
        mCurrentEngine->setShortUrl(urlStr);
        mCurrentEngine->generateShortUrl();
    } else {
        Q_EMIT message(i18n("String doesn't seem to be a URL"));
    }
}

void InsertShorturlPluginEditorInterface::slotShortUrlFailed(const QString &errMsg)
{
    Q_EMIT message(i18n("An error occurred: \"%1\"", errMsg));
}

#include "moc_insertshorturlplugineditorinterface.cpp"
