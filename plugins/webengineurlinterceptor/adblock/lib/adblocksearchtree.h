/*
  SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

  This file originates from QupZilla - WebKit based browser
  SPDX-FileCopyrightText: 2013-2014 David Rosca <nowrep@gmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QChar>
#include <QHash>

class QWebEngineUrlRequestInfo;
namespace AdBlock
{
class AdBlockRule;
class AdBlockSearchTree
{
public:
    AdBlockSearchTree();
    ~AdBlockSearchTree();

    void clear();

    Q_REQUIRED_RESULT bool add(const AdBlockRule *rule) const;
    const AdBlockRule *find(const QWebEngineUrlRequestInfo &request, const QString &domain, const QString &urlString) const;

private:
    struct Node {
        QChar c;
        const AdBlockRule *rule = nullptr;
        QHash<QChar, Node *> children;

        Node()
            : c(0)
        {
        }
    };

    const AdBlockRule *
    prefixSearch(const QWebEngineUrlRequestInfo &request, const QString &domain, const QString &urlString, const QChar *string, int len) const;

    void deleteNode(Node *node);

    Node *m_root = nullptr;
};
}
