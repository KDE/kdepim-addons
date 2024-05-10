/*
   SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownpreviewwidget.h"
#include "markdownconverter.h"
#include "markdownenginepage.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QWebChannel>
#include <QWebEngineSettings>
#include <QWebEngineView>

MarkdownPreviewWidget::MarkdownPreviewWidget(QWidget *parent)
    : QWidget(parent)
    , mWebView(new QWebEngineView(this))
    , mConverter(new MarkdownConverter(this))
    , mHoverUrlLabel(new QLabel(this))
{
    mConverter->setObjectName(QLatin1StringView("converter"));
    connect(mConverter, &MarkdownConverter::failed, this, &MarkdownPreviewWidget::converterFailed);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainLayout"));
    mainLayout->setContentsMargins({});

    auto page = new MarkdownEnginePage(this);
    mWebView->setPage(page);
    mWebView->resize(600, 800);

    mWebView->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::XSSAuditingEnabled, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::ErrorPageEnabled, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::HyperlinkAuditingEnabled, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::WebGLEnabled, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::AutoLoadIconsForPage, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, false);
    mWebView->settings()->setAttribute(QWebEngineSettings::WebGLEnabled, false);

    mWebView->setObjectName(QLatin1StringView("webengine"));
    mainLayout->addWidget(mWebView);

    mHoverUrlLabel->setObjectName(QLatin1StringView("mHoverUrlLabel"));
    mainLayout->addWidget(mHoverUrlLabel);

    mWebView->setContextMenuPolicy(Qt::NoContextMenu);
    connect(page, &MarkdownEnginePage::linkHovered, this, &MarkdownPreviewWidget::slotLinkHovered);
}

MarkdownPreviewWidget::~MarkdownPreviewWidget() = default;

void MarkdownPreviewWidget::slotLinkHovered(const QString &url)
{
    QString truncateUrl = url;
    if (truncateUrl.length() > 80) {
        truncateUrl.truncate(80);
        truncateUrl += QStringLiteral("…");
    }
    mHoverUrlLabel->setText(truncateUrl);
    mHoverUrlLabel->setToolTip(url);
}

void MarkdownPreviewWidget::converterFailed(const QString &msg)
{
    KMessageBox::error(this, i18n("Converter Error"), msg);
}

void MarkdownPreviewWidget::setConverterSettings(bool enableEmbeddedLabel, bool enableExtraDefinitionLists)
{
    mConverter->setEnableEmbeddedLabel(enableEmbeddedLabel);
    mConverter->setEnableExtraDefinitionLists(enableExtraDefinitionLists);
}

void MarkdownPreviewWidget::slotUpdatePreview(const QString &text)
{
    mWebView->setHtml(mConverter->convertTextToMarkdown(text), QUrl(QStringLiteral("file://")));
}

#include "moc_markdownpreviewwidget.cpp"
