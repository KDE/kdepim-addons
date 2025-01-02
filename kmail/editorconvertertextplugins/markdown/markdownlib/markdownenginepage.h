/*
    SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QWebEnginePage>

class MarkdownEnginePage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit MarkdownEnginePage(QObject *parent = nullptr);
    ~MarkdownEnginePage() override;

protected:
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame) override;
};
