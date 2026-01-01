/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerconfiguredialog.h"
using namespace Qt::Literals::StringLiterals;

#include "externalcomposerconfigurewidget.h"
#include <KLocalizedString>

ExternalComposerConfigureDialog::ExternalComposerConfigureDialog(QWidget *parent)
    : PimCommon::ConfigurePluginDialog(parent)
{
    setWindowTitle(i18nc("@title:window", "Configure \"External Composer\" Plugin"));
    initLayout();
}

ExternalComposerConfigureDialog::~ExternalComposerConfigureDialog() = default;

QWidget *ExternalComposerConfigureDialog::createLayout()
{
    mConfigureWidget = new ExternalComposerConfigureWidget(this);
    mConfigureWidget->setObjectName(QLatin1StringView("configurewidget"));
    return mConfigureWidget;
}

void ExternalComposerConfigureDialog::save()
{
    mConfigureWidget->saveSettings();
}

void ExternalComposerConfigureDialog::load()
{
    mConfigureWidget->loadSettings();
}

void ExternalComposerConfigureDialog::reset()
{
    mConfigureWidget->resetSettings();
}

void ExternalComposerConfigureDialog::help()
{
    showHelp(u"kmail2"_s, mConfigureWidget->helpAnchor());
}

#include "moc_externalcomposerconfiguredialog.cpp"
