/*
  Copyright (c) 2016-2018 Montel Laurent <montel@kde.org>
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
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
#include "adblockutil.h"
#include "adblockinterceptor_debug.h"

#include <KLocalizedString>
#include <QFile>
#include <QTimer>
#include <QNetworkReply>
#include <QStandardPaths>
#include <QSaveFile>
using namespace AdBlock;

AdBlockSubscription::AdBlockSubscription(const QString &title, QObject *parent)
    : QObject(parent)
    , mTitle(title)
    , mNetworkAccessManager(new QNetworkAccessManager(this))
{
}

QString AdBlockSubscription::title() const
{
    return mTitle;
}

QString AdBlockSubscription::filePath() const
{
    return mFilePath;
}

void AdBlockSubscription::setFilePath(const QString &path)
{
    mFilePath = path;
}

QUrl AdBlockSubscription::url() const
{
    return mUrl;
}

void AdBlockSubscription::setUrl(const QUrl &url)
{
    mUrl = url;
}

void AdBlockSubscription::loadSubscription(const QStringList &disabledRules)
{
    QFile file(mFilePath);
    //qCWarning(ADBLOCKINTERCEPTOR_LOG) << "loadSubscription:: loading path:" << mFilePath;
    if (!file.exists()) {
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
        return;
    }

    if (!file.open(QFile::ReadOnly)) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "Unable to open adblock file for reading" << mFilePath;
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
        return;
    }

    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    // Header is on 3rd line
    textStream.readLine(1024);
    textStream.readLine(1024);
    QString header = textStream.readLine(1024);

    if (!header.startsWith(QLatin1String("[Adblock")) || mTitle.isEmpty()) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "invalid format of adblock file" << mFilePath;
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
        return;
    }

    mRules.clear();

    while (!textStream.atEnd()) {
        AdBlockRule *rule = new AdBlockRule(textStream.readLine(), this);
        if (disabledRules.contains(rule->filter())) {
            rule->setEnabled(false);
        }

        mRules.append(rule);
    }

    // Initial update
    if (mRules.isEmpty() && !mUpdated) {
        QTimer::singleShot(0, this, &AdBlockSubscription::updateSubscription);
    }
}

void AdBlockSubscription::saveSubscription()
{
}

void AdBlockSubscription::updateSubscription()
{
    if (mReply || !mUrl.isValid()) {
        return;
    }
    mReply = mNetworkAccessManager->get(QNetworkRequest(mUrl));

    connect(mReply, &QNetworkReply::finished, this, &AdBlockSubscription::subscriptionDownloaded);
}

void AdBlockSubscription::subscriptionDownloaded()
{
    if (mReply != qobject_cast<QNetworkReply *>(sender())) {
        return;
    }

    bool error = false;
    const QByteArray response = QString::fromUtf8(mReply->readAll()).toUtf8();

    if (mReply->error() != QNetworkReply::NoError
        || !response.startsWith(QByteArray("[Adblock"))
        || !saveDownloadedData(response)
        ) {
        error = true;
    }

    mReply->deleteLater();
    mReply = nullptr;

    if (error) {
        Q_EMIT subscriptionError(i18n("Cannot load subscription!"));
        return;
    }

    loadSubscription(AdblockManager::self()->disabledRules());

    Q_EMIT subscriptionUpdated();
    Q_EMIT subscriptionChanged();
}

bool AdBlockSubscription::saveDownloadedData(const QByteArray &data)
{
    QSaveFile file(mFilePath);

    if (!file.open(QFile::WriteOnly)) {
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "Unable to open adblock file for writing:" << mFilePath;
        return false;
    }

    // Write subscription header
    file.write(QStringLiteral("Title: %1\nUrl: %2\n").arg(title(), url().toString()).toUtf8());
    file.write(data);
    file.commit();
    return true;
}

bool AdBlockSubscription::enabled() const
{
    return mEnabled;
}

void AdBlockSubscription::setEnabled(bool enabled)
{
    mEnabled = enabled;
}

const AdBlockRule *AdBlockSubscription::rule(int offset) const
{
    if (!AdblockUtil::containsIndex(mRules, offset)) {
        return nullptr;
    }

    return mRules[offset];
}

QVector<AdBlockRule *> AdBlockSubscription::allRules() const
{
    return mRules;
}

const AdBlockRule *AdBlockSubscription::enableRule(int offset)
{
    if (!AdblockUtil::containsIndex(mRules, offset)) {
        return nullptr;
    }

    AdBlockRule *rule = mRules[offset];
    rule->setEnabled(true);
    AdblockManager::self()->removeDisabledRule(rule->filter());

    Q_EMIT subscriptionChanged();
    return rule;
}

const AdBlockRule *AdBlockSubscription::disableRule(int offset)
{
    if (!AdblockUtil::containsIndex(mRules, offset)) {
        return nullptr;
    }

    AdBlockRule *rule = mRules[offset];
    rule->setEnabled(false);
    AdblockManager::self()->addDisabledRule(rule->filter());

    Q_EMIT subscriptionChanged();

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
    qDeleteAll(mRules);
}

// AdBlockCustomList

AdBlockCustomList::AdBlockCustomList(QObject *parent)
    : AdBlockSubscription(i18n("Custom Rules"), parent)
{
    setFilePath(AdBlock::AdblockUtil::localFilterPath());
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
    if (!file.exists()) {
        saveSubscription();
    }

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
        qCWarning(ADBLOCKINTERCEPTOR_LOG) << "Unable to open adblock file for writing:" << filePath();
        return;
    }

    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    textStream << "Title: " << title() << endl;
    textStream << "Url: " << url().toString() << endl;
    textStream << "[Adblock Plus 1.1.1]" << endl;

    foreach (const AdBlockRule *rule, mRules) {
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
    foreach (const AdBlockRule *rule, mRules) {
        if (rule->filter() == filter) {
            return true;
        }
    }

    return false;
}

bool AdBlockCustomList::removeFilter(const QString &filter)
{
    const int numberRules(mRules.count());
    for (int i = 0; i < numberRules; ++i) {
        const AdBlockRule *rule = mRules.at(i);

        if (rule->filter() == filter) {
            return removeRule(i);
        }
    }

    return false;
}

int AdBlockCustomList::addRule(AdBlockRule *rule)
{
    mRules.append(rule);

    Q_EMIT subscriptionChanged();

    return mRules.count() - 1;
}

bool AdBlockCustomList::removeRule(int offset)
{
    if (!AdblockUtil::containsIndex(mRules, offset)) {
        return false;
    }

    AdBlockRule *rule = mRules.at(offset);
    const QString filter = rule->filter();

    mRules.remove(offset);

    Q_EMIT subscriptionChanged();

    AdblockManager::self()->removeDisabledRule(filter);

    delete rule;
    return true;
}

const AdBlockRule *AdBlockCustomList::replaceRule(AdBlockRule *rule, int offset)
{
    if (!AdblockUtil::containsIndex(mRules, offset)) {
        return nullptr;
    }

    AdBlockRule *oldRule = mRules.at(offset);
    mRules[offset] = rule;

    Q_EMIT subscriptionChanged();

    delete oldRule;
    return mRules[offset];
}
