/*
    SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "markdownenginepage.h"
#include <QWebEngineProfile>
#include <QWebEngineSettings>

MarkdownEnginePage::MarkdownEnginePage(QObject *parent)
    : QWebEnginePage(parent)
{
    settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, false);
    settings()->setAttribute(QWebEngineSettings::PluginsEnabled, false);
    settings()->setAttribute(QWebEngineSettings::AutoLoadImages, true);
    settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, false);
    settings()->setAttribute(QWebEngineSettings::JavascriptCanAccessClipboard, false);
    settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, false);
    settings()->setAttribute(QWebEngineSettings::XSSAuditingEnabled, false);
    settings()->setAttribute(QWebEngineSettings::ErrorPageEnabled, false);
    settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, false);
    settings()->setAttribute(QWebEngineSettings::ScreenCaptureEnabled, false);
    settings()->setAttribute(QWebEngineSettings::WebGLEnabled, false);
    settings()->setAttribute(QWebEngineSettings::AutoLoadIconsForPage, false);
    settings()->setAttribute(QWebEngineSettings::Accelerated2dCanvasEnabled, false);
    settings()->setAttribute(QWebEngineSettings::WebGLEnabled, false);

    settings()->setAttribute(QWebEngineSettings::FocusOnNavigationEnabled, false);
    settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, false);

    settings()->setAttribute(QWebEngineSettings::ShowScrollBars, true);
    settings()->setAttribute(QWebEngineSettings::AllowWindowActivationFromJavaScript, false);
    settings()->setAttribute(QWebEngineSettings::PlaybackRequiresUserGesture, false);
    settings()->setAttribute(QWebEngineSettings::JavascriptCanPaste, false);
    settings()->setAttribute(QWebEngineSettings::WebRTCPublicInterfacesOnly, false);
    settings()->setAttribute(QWebEngineSettings::PdfViewerEnabled, false);
    profile()->setPersistentCookiesPolicy(QWebEngineProfile::NoPersistentCookies);
}

MarkdownEnginePage::~MarkdownEnginePage() = default;

bool MarkdownEnginePage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
    Q_UNUSED(type)
    Q_UNUSED(isMainFrame)
    if (url.scheme() == QLatin1StringView("data")) {
        return true;
    }
    return false;
}

#include "moc_markdownenginepage.cpp"
