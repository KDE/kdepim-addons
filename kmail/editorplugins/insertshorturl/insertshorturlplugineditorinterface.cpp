/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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
#include <KPIMTextEdit/RichTextEditor>
#include <KLocalizedString>
#include <KActionCollection>
#include <QAction>
#include <KSharedConfig>
#include <KSharedConfig>
#include <KConfigGroup>
#include "shorturlengineplugin/shorturlengineinterface.h"
#include "shorturlengineplugin/shorturlengineplugin.h"
#include "shorturlengineplugin/shorturlenginepluginmanager.h"

InsertShorturlPluginEditorInterface::InsertShorturlPluginEditorInterface(QObject *parent)
    : MessageComposer::PluginEditorInterface(parent)
{
    initializePlugins();
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
        disconnect(mCurrentEngine, &ShortUrlEngineInterface::shortUrlGenerated, this, &InsertShorturlPluginEditorInterface::slotShortUrlDone);
        disconnect(mCurrentEngine, &ShortUrlEngineInterface::shortUrlFailed, this, &InsertShorturlPluginEditorInterface::slotShortUrlFailed);
    }

    KConfigGroup grp(KSharedConfig::openConfig(), "ShortUrl");
    const QString engineName = grp.readEntry("EngineName");
    mCurrentEngine = mLstInterface.value(engineName);
    if (!mCurrentEngine && !mLstInterface.isEmpty()) {
        mCurrentEngine = mLstInterface.cbegin().value();
    }

    if (mCurrentEngine) {
        connect(mCurrentEngine, &ShortUrlEngineInterface::shortUrlGenerated, this, &InsertShorturlPluginEditorInterface::slotShortUrlDone);
        connect(mCurrentEngine, &ShortUrlEngineInterface::shortUrlFailed, this, &InsertShorturlPluginEditorInterface::slotShortUrlFailed);
    }
}


void InsertShorturlPluginEditorInterface::createAction(KActionCollection *ac)
{
    QAction *action = new QAction(i18n("Insert Short Url..."), this);
    ac->addAction(QStringLiteral("insert_shortulr"), action);
    connect(action, &QAction::triggered, this, &InsertShorturlPluginEditorInterface::slotActivated);
    MessageComposer::ActionType type(action, MessageComposer::ActionType::PopupMenu);
    setActionType(type);
}

void InsertShorturlPluginEditorInterface::slotActivated()
{
    Q_EMIT emitPluginActivated(this);
}

void InsertShorturlPluginEditorInterface::exec()
{
    QTextCursor textCursor = richTextEditor()->textCursor();
    if (textCursor.hasSelection()) {
        QString urlStr = textCursor.selectedText();
        if (urlStr.startsWith(QLatin1String("http:")) || urlStr.startsWith(QLatin1String("https:"))) {
            /*
            if (!mCurrentEngine) {
                return;
            }
            if (!PimCommon::NetworkManager::self()->networkConfigureManager()->isOnline()) {
                KMessageBox::information(this, i18n("No network connection detected, we cannot shorten URL."), i18n("No network"));
                return;
            }
            if (mOriginalUrl->text().isEmpty()) {
                return;
            }
            mIndicatorLabel->start();
            mCurrentEngine->setShortUrl(mOriginalUrl->text());
            mShortUrl->clear();
            mCurrentEngine->generateShortUrl();
            */
            //textCursor.insertText(newText);
        }
    }
    //editorUtil.upperCase(textCursor);

}
void InsertShorturlPluginEditorInterface::slotShortUrlDone(const QString &url)
{
    //mIndicatorLabel->stop();
}

void InsertShorturlPluginEditorInterface::slotShortUrlFailed(const QString &errMsg)
{
    //KMessageBox::error(this, i18n("An error occurred: \"%1\"", errMsg));
    //mIndicatorLabel->stop();
}

