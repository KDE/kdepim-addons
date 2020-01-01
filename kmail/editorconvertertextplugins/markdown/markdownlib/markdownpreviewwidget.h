/*
   Copyright (C) 2018-2020 Laurent Montel <montel@kde.org>

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
