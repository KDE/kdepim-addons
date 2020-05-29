/*
    Copyright (C) 2018-2020 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#include "markdownenginepage.h"
#include <QWebEngineSettings>
#include <QWebEngineProfile>

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
    //settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, false);
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

MarkdownEnginePage::~MarkdownEnginePage()
{
}

bool MarkdownEnginePage::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
    Q_UNUSED(type);
    Q_UNUSED(isMainFrame);
    if (url.scheme() == QLatin1String("data")) {
        return true;
    }
    return false;
}
