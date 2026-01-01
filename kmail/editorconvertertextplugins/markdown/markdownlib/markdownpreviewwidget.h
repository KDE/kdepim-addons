/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "markdownlib_private_export.h"
#include <QWidget>
class QWebEngineView;
class MarkdownConverter;
class QLabel;
class LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT MarkdownPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MarkdownPreviewWidget(QWidget *parent = nullptr);
    ~MarkdownPreviewWidget() override;
    void setConverterSettings(bool enableEmbeddedLabel, bool enableExtraDefinitionLists);

public Q_SLOTS:
    void slotUpdatePreview(const QString &text);

private:
    void slotLinkHovered(const QString &url);
    void converterFailed(const QString &msg);
    QWebEngineView *const mWebView;
    MarkdownConverter *const mConverter;
    QLabel *const mHoverUrlLabel;
};
