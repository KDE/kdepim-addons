/*
  Copyright (c) 2016-2017 Montel Laurent <montel@kde.org>
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2014  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
/**
 * Copyright (c) 2009, Benjamin C. Meyer <ben@meyerhome.net>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Benjamin Meyer nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include "adblocksubscription.h"
#include "adblockmanager.h"
#include "adblocksearchtree.h"
//#include "networkmanager.h"
//#include "datapaths.h"
#include "adblockutil.h"
//#include "followredirectreply.h"
#include "adblockinterceptor_debug.h"

#include <KLocalizedString>
#include <QFile>
#include <QTimer>
#include <QNetworkReply>
using namespace AdBlock;

AdBlockSubscription::AdBlockSubscription(const QString &title, QObject *parent)
    : QObject(parent)
    , m_reply(0)
    , m_title(title)
    , m_updated(false)
{
}

QString AdBlockSubscription::title() const
{
    return m_title;
}

QString AdBlockSubscription::filePath() const
{
    return m_filePath;
}

void AdBlockSubscription::setFilePath(const QString &path)
{
    m_filePath = path;
}

QUrl AdBlockSubscription::url() const
{
    return m_url;
}

void AdBlockSubscription::setUrl(const QUrl &url)
{
    m_url = url;
}

void AdBlockSubscription::loadSubscription(const QStringList &disabledRules)
{
    QFile file(m_filePath);

    if (!file.exists()) {
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
        return;
    }

    if (!file.open(QFile::ReadOnly)) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "AdBlockSubscription::" << __FUNCTION__ << "Unable to open adblock file for reading" << m_filePath;
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
        return;
    }

    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    // Header is on 3rd line
    textStream.readLine(1024);
    textStream.readLine(1024);
    QString header = textStream.readLine(1024);

    if (!header.startsWith(QLatin1String("[Adblock")) || m_title.isEmpty()) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "AdBlockSubscription::" << __FUNCTION__ << "invalid format of adblock file" << m_filePath;
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
        return;
    }

    m_rules.clear();

    while (!textStream.atEnd()) {
        AdBlockRule *rule = new AdBlockRule(textStream.readLine(), this);

        if (disabledRules.contains(rule->filter())) {
            rule->setEnabled(false);
        }

        m_rules.append(rule);
    }

    // Initial update
    if (m_rules.isEmpty() && !m_updated) {
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
    }
}

void AdBlockSubscription::saveSubscription()
{
}

void AdBlockSubscription::updateSubscription()
{
#if 0
    if (m_reply || !m_url.isValid()) {
        return;
    }

    m_reply = new FollowRedirectReply(m_url, mApp->networkManager());

    connect(m_reply, SIGNAL(finished()), this, SLOT(subscriptionDownloaded()));
#endif
}

void AdBlockSubscription::subscriptionDownloaded()
{
#if 0
    if (m_reply != qobject_cast<FollowRedirectReply *>(sender())) {
        return;
    }

    bool error = false;
    const QByteArray response = QString::fromUtf8(m_reply->readAll()).toUtf8();

    if (m_reply->error() != QNetworkReply::NoError
        || !response.startsWith(QByteArray("[Adblock"))
        || !saveDownloadedData(response)
        ) {
        error = true;
    }

    m_reply->deleteLater();
    m_reply = 0;

    if (error) {
        Q_EMIT subscriptionError(i18n("Cannot load subscription!"));
        return;
    }

    loadSubscription(AdBlockManager::instance()->disabledRules());

    Q_EMIT subscriptionUpdated();
    Q_EMIT subscriptionChanged();
#endif
}

bool AdBlockSubscription::saveDownloadedData(const QByteArray &data)
{
#if 0
    QFile file(m_filePath);

    if (!file.open(QFile::ReadWrite | QFile::Truncate)) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "AdBlockSubscription::" << __FUNCTION__ << "Unable to open adblock file for writing:" << m_filePath;
        return false;
    }

    // Write subscription header
    file.write(QString("Title: %1\nUrl: %2\n").arg(title(), url().toString()).toUtf8());

    if (AdBlockManager::instance()->useLimitedEasyList() && m_url == QUrl(ADBLOCK_EASYLIST_URL)) {
        // Third-party advertisers rules are with start domain (||) placeholder which needs regexps
        // So we are ignoring it for keeping good performance
        // But we will use whitelist rules at the end of list

        QByteArray part1 = data.left(data.indexOf(QLatin1String("!-----------------------------Third-party adverts-----------------------------!")));
        QByteArray part2 = data.mid(data.indexOf(QLatin1String("!---------------------------------Whitelists----------------------------------!")));

        file.write(part1);
        file.write(part2);
        file.close();
        return true;
    }

    file.write(data);
    file.close();
#else
    Q_UNUSED(data);
#endif
    return true;
}

const AdBlockRule *AdBlockSubscription::rule(int offset) const
{
    if (!AdblockUtil::containsIndex(m_rules, offset)) {
        return 0;
    }

    return m_rules[offset];
}

QVector<AdBlockRule *> AdBlockSubscription::allRules() const
{
    return m_rules;
}

const AdBlockRule *AdBlockSubscription::enableRule(int offset)
{
    if (!AdblockUtil::containsIndex(m_rules, offset)) {
        return nullptr;
    }

    AdBlockRule *rule = m_rules[offset];
    rule->setEnabled(true);
    //FIXME AdBlockManager::instance()->removeDisabledRule(rule->filter());

    Q_EMIT subscriptionChanged();

    if (rule->isCssRule()) {
        //FIXME mApp->reloadUserStyleSheet();
    }

    return rule;
}

const AdBlockRule *AdBlockSubscription::disableRule(int offset)
{
    if (!AdblockUtil::containsIndex(m_rules, offset)) {
        return nullptr;
    }

    AdBlockRule *rule = m_rules[offset];
    rule->setEnabled(false);
    //FIXME AdBlockManager::instance()->addDisabledRule(rule->filter());

    Q_EMIT subscriptionChanged();

    if (rule->isCssRule()) {
        //FIXME mApp->reloadUserStyleSheet();
    }

    return rule;
}

bool AdBlockSubscription::canEditRules() const
{
    return false;
}

bool AdBlockSubscription::canBeRemoved() const
{
    return true;
}

int AdBlockSubscription::addRule(AdBlockRule *rule)
{
    Q_UNUSED(rule)
    return -1;
}

bool AdBlockSubscription::removeRule(int offset)
{
    Q_UNUSED(offset)
    return false;
}

const AdBlockRule *AdBlockSubscription::replaceRule(AdBlockRule *rule, int offset)
{
    Q_UNUSED(rule)
    Q_UNUSED(offset)
    return nullptr;
}

AdBlockSubscription::~AdBlockSubscription()
{
    qDeleteAll(m_rules);
}

// AdBlockCustomList

AdBlockCustomList::AdBlockCustomList(QObject *parent)
    : AdBlockSubscription(i18n("Custom Rules"), parent)
{
#if 0
    setFilePath(DataPaths::currentProfilePath() + QLatin1String("/adblock/customlist.txt"));
#endif
}

void AdBlockCustomList::loadSubscription(const QStringList &disabledRules)
{
    // DuckDuckGo ad whitelist rules
    // They cannot be removed, but can be disabled.
    // Please consider not disabling them. Thanks!

    const QString ddg1 = QStringLiteral("@@||duckduckgo.com^$document");
    const QString ddg2 = QStringLiteral("duckduckgo.com#@#.has-ad");

    const QString rules = QString::fromUtf8(readAllFileByteContents(filePath()));

    QFile file(filePath());
    if (file.open(QFile::WriteOnly | QFile::Append)) {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        if (!rules.contains(ddg1 + QLatin1String("\n"))) {
            stream << ddg1 << endl;
        }

        if (!rules.contains(QLatin1String("\n") + ddg2)) {
            stream << ddg2 << endl;
        }
    }
    file.close();

    AdBlockSubscription::loadSubscription(disabledRules);
}

QByteArray AdBlockCustomList::readAllFileByteContents(const QString &filename)
{
    QFile file(filename);

    if (!filename.isEmpty() && file.open(QFile::ReadOnly)) {
        const QByteArray a = file.readAll();
        file.close();
        return a;
    }

    return QByteArray();
}
void AdBlockCustomList::saveSubscription()
{
    QFile file(filePath());

    if (!file.open(QFile::ReadWrite | QFile::Truncate)) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "AdBlockSubscription::" << __FUNCTION__ << "Unable to open adblock file for writing:" << filePath();
        return;
    }

    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    textStream << "Title: " << title() << endl;
    textStream << "Url: " << url().toString() << endl;
    textStream << "[Adblock Plus 1.1.1]" << endl;

    foreach (const AdBlockRule *rule, m_rules) {
        textStream << rule->filter() << endl;
    }

    file.close();
}

bool AdBlockCustomList::canEditRules() const
{
    return true;
}

bool AdBlockCustomList::canBeRemoved() const
{
    return false;
}

bool AdBlockCustomList::containsFilter(const QString &filter) const
{
    foreach (const AdBlockRule *rule, m_rules) {
        if (rule->filter() == filter) {
            return true;
        }
    }

    return false;
}

bool AdBlockCustomList::removeFilter(const QString &filter)
{
    const int numberRules(m_rules.count());
    for (int i = 0; i < numberRules; ++i) {
        const AdBlockRule *rule = m_rules.at(i);

        if (rule->filter() == filter) {
            return removeRule(i);
        }
    }

    return false;
}

int AdBlockCustomList::addRule(AdBlockRule *rule)
{
    m_rules.append(rule);

    Q_EMIT subscriptionChanged();

    if (rule->isCssRule()) {
        //FIXME mApp->reloadUserStyleSheet();
    }

    return m_rules.count() - 1;
}

bool AdBlockCustomList::removeRule(int offset)
{
    if (!AdblockUtil::containsIndex(m_rules, offset)) {
        return false;
    }

    AdBlockRule *rule = m_rules.at(offset);
    const QString filter = rule->filter();

    m_rules.remove(offset);

    Q_EMIT subscriptionChanged();

    if (rule->isCssRule()) {
        //FIXME mApp->reloadUserStyleSheet();
    }

    //FIXME AdBlockManager::instance()->removeDisabledRule(filter);

    delete rule;
    return true;
}

const AdBlockRule *AdBlockCustomList::replaceRule(AdBlockRule *rule, int offset)
{
    if (!AdblockUtil::containsIndex(m_rules, offset)) {
        return nullptr;
    }

    AdBlockRule *oldRule = m_rules.at(offset);
    m_rules[offset] = rule;

    Q_EMIT subscriptionChanged();

    if (rule->isCssRule() || oldRule->isCssRule()) {
        //FIXME mApp->reloadUserStyleSheet();
    }

    delete oldRule;
    return m_rules[offset];
}
