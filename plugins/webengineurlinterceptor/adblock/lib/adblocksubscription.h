/*
  SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

  This file originates from QupZilla - WebKit based browser
  SPDX-FileCopyrightText: 2013-2014 David Rosca <nowrep@gmail.com>
  SPDX-FileCopyrightText: 2009 Benjamin C. Meyer <ben@meyerhome.net>

  SPDX-License-Identifier: GPL-2.0-or-later OR BSD-3-Clause
*/

#pragma once

#include <QUrl>
#include <QVector>

#include "adblockrule.h"
#include "adblocksearchtree.h"

class QNetworkAccessManager;
class QNetworkReply;
namespace AdBlock
{
class AdBlockSubscription : public QObject
{
    Q_OBJECT
public:
    explicit AdBlockSubscription(const QString &title, QObject *parent = nullptr);
    ~AdBlockSubscription() override;

    Q_REQUIRED_RESULT QString title() const;

    Q_REQUIRED_RESULT QString filePath() const;
    void setFilePath(const QString &path);

    Q_REQUIRED_RESULT QUrl url() const;
    void setUrl(const QUrl &url);

    virtual void loadSubscription(const QStringList &disabledRules);
    virtual void saveSubscription();

    const AdBlockRule *rule(int offset) const;
    QVector<AdBlockRule *> allRules() const;

    const AdBlockRule *enableRule(int offset);
    const AdBlockRule *disableRule(int offset);

    Q_REQUIRED_RESULT virtual bool canEditRules() const;
    Q_REQUIRED_RESULT virtual bool canBeRemoved() const;

    Q_REQUIRED_RESULT virtual int addRule(AdBlockRule *rule);
    Q_REQUIRED_RESULT virtual bool removeRule(int offset);
    virtual const AdBlockRule *replaceRule(AdBlockRule *rule, int offset);

    Q_REQUIRED_RESULT bool enabled() const;
    void setEnabled(bool enabled);

public Q_SLOTS:
    void updateSubscription();

Q_SIGNALS:
    void subscriptionChanged();
    void subscriptionUpdated();
    void subscriptionError(const QString &message);

protected Q_SLOTS:
    void subscriptionDownloaded();

protected:
    virtual bool saveDownloadedData(const QByteArray &data);

    QNetworkReply *mReply = nullptr;
    QVector<AdBlockRule *> mRules;

private:
    QString mTitle;
    QString mFilePath;

    QUrl mUrl;
    QNetworkAccessManager *mNetworkAccessManager = nullptr;
    bool mUpdated = false;
    bool mEnabled = true;
};

class AdBlockCustomList : public AdBlockSubscription
{
    Q_OBJECT
public:
    explicit AdBlockCustomList(QObject *parent = nullptr);

    void loadSubscription(const QStringList &disabledRules) override;
    void saveSubscription() override;

    bool canEditRules() const override;
    bool canBeRemoved() const override;

    bool containsFilter(const QString &filter) const;
    bool removeFilter(const QString &filter);

    int addRule(AdBlockRule *rule) override;
    bool removeRule(int offset) override;
    const AdBlockRule *replaceRule(AdBlockRule *rule, int offset) override;

private:
    QByteArray readAllFileByteContents(const QString &filename);
};
}
