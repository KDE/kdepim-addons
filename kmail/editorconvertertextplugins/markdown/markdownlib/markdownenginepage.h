/*
    SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef MARKDOWNENGINEPAGE_H
#define MARKDOWNENGINEPAGE_H

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

#endif // MARKDOWNENGINEPAGE_H
