/*
   SPDX-FileCopyrightText: 2018-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "markdownconfiguredialog.h"
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
    mConfigureWidget->setObjectName(QStringLiteral("configurewidget"));
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
    QDesktopServices::openUrl(QUrl(QStringLiteral("https://tools.ietf.org/html/rfc7763")));
}

#include "moc_markdownconfiguredialog.cpp"
