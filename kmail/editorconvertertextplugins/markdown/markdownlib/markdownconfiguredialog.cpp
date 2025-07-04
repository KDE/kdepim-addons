/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;

#include "markdownconfigurewidget.h"
#include <KLocalizedString>
#include <QDesktopServices>
#include <QUrl>

MarkdownConfigureDialog::MarkdownConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure Markdown Plugin"));
    initLayout();
}

MarkdownConfigureDialog::~MarkdownConfigureDialog() = default;

QWidget *MarkdownConfigureDialog::createLayout()
{
    mConfigureWidget = new MarkdownConfigureWidget(this);
    mConfigureWidget->setObjectName(QLatin1StringView("configurewidget"));
    return mConfigureWidget;
}

void MarkdownConfigureDialog::save()
{
    mConfigureWidget->saveSettings();
}

void MarkdownConfigureDialog::load()
{
    mConfigureWidget->loadSettings();
}

void MarkdownConfigureDialog::reset()
{
    mConfigureWidget->resetSettings();
}

void MarkdownConfigureDialog::help()
{
    QDesktopServices::openUrl(QUrl(u"https://tools.ietf.org/html/rfc7763"_s));
}

#include "moc_markdownconfiguredialog.cpp"
