/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "autogenerateconfigureaskdialog.h"
#include "autogenerateconfigureaskwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>

namespace
{
const char myAutogenerateConfigureAskDialogGroupName[] = "AutogenerateConfigureAskDialog";
}
AutogenerateConfigureAskDialog::AutogenerateConfigureAskDialog(QWidget *parent)
    : QDialog(parent)
    , mAutogenerateConfigureAskWidget(new AutogenerateConfigureAskWidget(this))
{
    setWindowTitle(i18nc("@title:window", "Administrator"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mAutogenerateConfigureAskWidget->setObjectName(QStringLiteral("mAutogenerateConfigureAskWidget"));
    mainLayout->addWidget(mAutogenerateConfigureAskWidget);

    auto button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    button->setObjectName(QStringLiteral("button"));
    mainLayout->addWidget(button);
    connect(button, &QDialogButtonBox::rejected, this, &AutogenerateConfigureAskDialog::reject);
    connect(button, &QDialogButtonBox::accepted, this, &AutogenerateConfigureAskDialog::accept);

    readConfig();
}

AutogenerateConfigureAskDialog::~AutogenerateConfigureAskDialog()
{
    writeConfig();
}

void AutogenerateConfigureAskDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myAutogenerateConfigureAskDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void AutogenerateConfigureAskDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myAutogenerateConfigureAskDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_autogenerateconfigureaskdialog.cpp"
