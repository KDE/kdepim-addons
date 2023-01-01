/*
  SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

  This file originates from QupZilla - WebKit based browser
  SPDX-FileCopyrightText: 2013-2014 David Rosca <nowrep@gmail.com>
  SPDX-FileCopyrightText: 2009 Benjamin C. Meyer <ben@meyerhome.net>

  SPDX-License-Identifier: GPL-2.0-or-later OR BSD-3-Clause
*/

#pragma once

#include "adblockregexp.h"
#include <QStringList>
#include <QStringMatcher>
class QUrl;
class QWebEngineUrlRequestInfo;

namespace AdBlock
{
class AdBlockSubscription;

class AdBlockRule
{
    Q_DISABLE_COPY(AdBlockRule)

public:
    AdBlockRule(const QString &filter = QString(), AdBlockSubscription *subscription = nullptr);
    ~AdBlockRule();

    AdBlockRule *copy() const;

    AdBlockSubscription *subscription() const;
    void setSubscription(AdBlockSubscription *subscription);

    Q_REQUIRED_RESULT QString filter() const;
    void setFilter(const QString &filter);

    Q_REQUIRED_RESULT bool isCssRule() const;
    Q_REQUIRED_RESULT QString cssSelector() const;

    Q_REQUIRED_RESULT bool isDocument() const;
    Q_REQUIRED_RESULT bool isElemhide() const;

    Q_REQUIRED_RESULT bool isDomainRestricted() const;
    Q_REQUIRED_RESULT bool isException() const;

    Q_REQUIRED_RESULT bool isComment() const;
    Q_REQUIRED_RESULT bool isEnabled() const;
    void setEnabled(bool enabled);

    Q_REQUIRED_RESULT bool isSlow() const;
    Q_REQUIRED_RESULT bool isInternalDisabled() const;

    bool urlMatch(const QUrl &url) const;
    bool networkMatch(const QWebEngineUrlRequestInfo &request, const QString &domain, const QString &encodedUrl) const;

    bool matchDomain(const QString &domain) const;
    bool matchThirdParty(const QWebEngineUrlRequestInfo &request) const;
    bool matchObject(const QWebEngineUrlRequestInfo &request) const;
    bool matchSubdocument(const QWebEngineUrlRequestInfo &request) const;
    bool matchXmlHttpRequest(const QWebEngineUrlRequestInfo &request) const;
    bool matchImage(const QWebEngineUrlRequestInfo &request) const;
    bool matchScript(const QWebEngineUrlRequestInfo &request) const;
    bool matchStyleSheet(const QWebEngineUrlRequestInfo &request) const;
    bool matchObjectSubrequest(const QWebEngineUrlRequestInfo &request) const;

protected:
    bool stringMatch(const QString &domain, const QString &encodedUrl) const;
    bool isMatchingDomain(const QString &domain, const QString &filter) const;
    bool isMatchingRegExpStrings(const QString &url) const;
    Q_REQUIRED_RESULT QStringList parseRegExpFilter(const QString &filter) const;

private:
    enum RuleType {
        CssRule = 0,
        DomainMatchRule = 1,
        RegExpMatchRule = 2,
        StringEndsMatchRule = 3,
        StringContainsMatchRule = 4,
        Invalid = 5,
    };

    enum RuleOption {
        DomainRestrictedOption = 1,
        ThirdPartyOption = 2,
        ObjectOption = 4,
        SubdocumentOption = 8,
        XMLHttpRequestOption = 16,
        ImageOption = 32,
        ScriptOption = 64,
        StyleSheetOption = 128,
        ObjectSubrequestOption = 256,

        // Exception only options
        DocumentOption = 1024,
        ElementHideOption = 2048,
    };

    Q_DECLARE_FLAGS(RuleOptions, RuleOption)

    inline bool hasOption(RuleOption opt) const;
    inline bool hasException(RuleOption opt) const;

    inline void setOption(RuleOption opt);
    inline void setException(RuleOption opt, bool on);

    void parseFilter();
    void parseDomains(const QString &domains, QChar separator);
    bool filterIsOnlyDomain(const QString &filter) const;
    bool filterIsOnlyEndsMatch(const QString &filter) const;
    QString createRegExpFromFilter(const QString &filter) const;
    QList<QStringMatcher> createStringMatchers(const QStringList &filters) const;

    AdBlockSubscription *m_subscription = nullptr;

    RuleType m_type;
    RuleOptions m_options;
    RuleOptions m_exceptions;

    // Original rule filter
    QString m_filter;
    // Parsed rule for string matching (CSS Selector for CSS rules)
    QString m_matchString;
    // Case sensitivity for string matching
    Qt::CaseSensitivity m_caseSensitivity;

    bool m_isEnabled;
    bool m_isException;
    bool m_isInternalDisabled;

    QStringList m_allowedDomains;
    QStringList m_blockedDomains;

    struct RegExp {
        AdblockRegExp regExp;
        QList<QStringMatcher> matchers;
    };

    // Use dynamic allocation to save memory
    RegExp *m_regExp = nullptr;

    friend class AdBlockMatcher;
    friend class AdBlockSearchTree;
    friend class AdBlockSubscription;
};
}
