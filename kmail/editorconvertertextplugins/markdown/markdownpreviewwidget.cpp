/*
   Copyright (C) 2018 Montel Laurent <montel@kde.org>

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

#include "markdownpreviewwidget.h"
#include "markdownconverter.h"
#include <QHBoxLayout>
#include <QWebChannel>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEngineView>

MarkdownPreviewWidget::MarkdownPreviewWidget(QWidget *parent)
    : QWidget(parent)
{
    mConverter = new MarkdownConverter(this);
    mConverter->setObjectName(QStringLiteral("converter"));

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setMargin(0);

    mWebView = new QWebEngineView(this);
    mWebView->resize(600, 800);

    mWebView->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    mWebView->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);

    mWebView->setObjectName(QStringLiteral("webengine"));
    mainLayout->addWidget(mWebView);
    mWebView->setContextMenuPolicy(Qt::NoContextMenu);
}

MarkdownPreviewWidget::~MarkdownPreviewWidget()
{
}

void MarkdownPreviewWidget::setConverterSettings(bool enableEmbeddedLabel, bool enableExtraDefinitionLists)
{
    mConverter->setEnableEmbeddedLabel(enableEmbeddedLabel);
    mConverter->setEnableExtraDefinitionLists(enableExtraDefinitionLists);
}

void MarkdownPreviewWidget::slotUpdatePreview(const QString &text)
{    
    mWebView->setHtml(mConverter->convertTextToMarkdown(text));
}
