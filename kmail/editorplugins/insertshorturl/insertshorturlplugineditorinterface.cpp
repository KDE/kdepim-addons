/*
   Copyright (C) 2017-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "insertshorturlplugineditorinterface.h"
#include "kmail_insertshorturl_debug.h"
#include <KPIMTextEdit/RichTextEditor>
#include <PimCommon/NetworkManager>
#include <KLocalizedString>
#include <KActionCollection>
#include <KSharedConfig>
#include <KSharedConfig>
#include <KConfigGroup>
#include <QAction>
#include <QNetworkConfigurationManager>
#include "shorturlengineplugin/shorturlengineinterface.h"
#include "shorturlengineplugin/shorturlengineplugin.h"
#include "shorturlengineplugin/shorturlenginepluginmanager.h"

InsertShorturlPluginEditorInterface::InsertShorturlPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
    setNeedSelectedText(true);
    initializePlugins();
    loadEngine();
}

InsertShorturlPluginEditorInterface::~InsertShorturlPluginEditorInterface()
{
}

void InsertShorturlPluginEditorInterface::initializePlugins()
{
    const QVector<ShortUrlEnginePlugin *> lstPlugin = ShortUrlEnginePluginManager::self()->pluginsList();
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

    KConfigGroup grp(KSharedConfig::openConfig(), "ShortUrl");
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
    QAction *action = new QAction(i18n("Insert Short URL..."), this);
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
    QString urlStr = textCursor.selectedText();

    if (urlStr.startsWith(QLatin1String("http:")) || urlStr.startsWith(QLatin1String("https:"))
        || urlStr.startsWith(QLatin1String("ftp:")) || urlStr.startsWith(QLatin1String("ftps:"))) {
        if (!mCurrentEngine) {
            qCWarning(KMAIL_INSERTSHORTURL_LOG) << "Current Engine not defined";
            return;
        }
        if (!PimCommon::NetworkManager::self()->networkConfigureManager()->isOnline()) {
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
