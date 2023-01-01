/*
   SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "akonadidatabasetoolsdialog.h"
#include "akonadidatabasetoolswidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
static const char myConfigGroupName[] = "AkonadiDatabaseToolsDialog";
}

AkonadiDatabaseToolsDialog::AkonadiDatabaseToolsDialog(QWidget *parent)
    : QDialog(parent)
    , mAkonadiDatabaseToolsWidget(new AkonadiDatabaseToolsWidget(this))
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(i18nc("@title:window", "Akonadi Database Tool"));
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));

    mAkonadiDatabaseToolsWidget->setObjectName(QStringLiteral("mAkonadiDatabaseToolsWidget"));
    mainLayout->addWidget(mAkonadiDatabaseToolsWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Close, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &AkonadiDatabaseToolsDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &AkonadiDatabaseToolsDialog::reject);
    readConfig();
}

AkonadiDatabaseToolsDialog::~AkonadiDatabaseToolsDialog()
{
    writeConfig();
}

void AkonadiDatabaseToolsDialog::appendText(const QString &text)
{
    mAkonadiDatabaseToolsWidget->appendText(text);
}

void AkonadiDatabaseToolsDialog::appendErrorText(const QString &text)
{
    mAkonadiDatabaseToolsWidget->appendText(QStringLiteral("<font color=#FF0000>%1</font>").arg(text));
}

void AkonadiDatabaseToolsDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

void AkonadiDatabaseToolsDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(500, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), myConfigGroupName);
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}
