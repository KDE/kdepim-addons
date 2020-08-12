/*
   SPDX-FileCopyrightText: 2018-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MARKDOWNPREVIEWWIDGET_H
#define MARKDOWNPREVIEWWIDGET_H

#include <QWidget>
#include "markdownlib_private_export.h"
class QWebEngineView;
class MarkdownConverter;
class QLabel;
class LIBKMAILMARKDOWNPRIVATE_TESTS_EXPORT MarkdownPreviewWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MarkdownPreviewWidget(QWidget *parent = nullptr);
    ~MarkdownPreviewWidget();
    void setConverterSettings(bool enableEmbeddedLabel, bool enableExtraDefinitionLists);

public Q_SLOTS:
    void slotUpdatePreview(const QString &text);

private:
    void slotLinkHovered(const QString &url);
    void converterFailed(const QString &msg);
    QWebEngineView *mWebView = nullptr;
    MarkdownConverter *mConverter = nullptr;
    QLabel *mHoverUrlLabel = nullptr;
};

#endif // MARKDOWNPREVIEWWIDGET_H
