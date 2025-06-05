/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "autogenerateanswerseditordialog.h"
#include "autogenerateanswerseditorwidget.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KWindowConfig>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QWindow>
namespace
{
const char myAutoGenerateAnswersEditorDialogGroupName[] = "AutoGenerateAnswersEditorDialog";
}
AutoGenerateAnswersEditorDialog::AutoGenerateAnswersEditorDialog(QWidget *parent)
    : QDialog(parent)
    , mAutoGenerateAnswersEditorWidget(new AutoGenerateAnswersEditorWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QLatin1StringView("mainlayout"));
    mAutoGenerateAnswersEditorWidget->setObjectName(QStringLiteral("mAutoGenerateAnswersEditorWidget"));
    mainLayout->addWidget(mAutoGenerateAnswersEditorWidget);

    auto box = new QDialogButtonBox(QDialogButtonBox::Close, this);
    box->setObjectName(QStringLiteral("box"));
    mainLayout->addWidget(box);
    connect(box, &QDialogButtonBox::accepted, this, &AutoGenerateAnswersEditorDialog::accept);
    connect(box, &QDialogButtonBox::rejected, this, &AutoGenerateAnswersEditorDialog::reject);
    readConfig();
}

AutoGenerateAnswersEditorDialog::~AutoGenerateAnswersEditorDialog()
{
    writeConfig();
}

void AutoGenerateAnswersEditorDialog::readConfig()
{
    create(); // ensure a window is created
    windowHandle()->resize(QSize(400, 300));
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myAutoGenerateAnswersEditorDialogGroupName));
    KWindowConfig::restoreWindowSize(windowHandle(), group);
    resize(windowHandle()->size()); // workaround for QTBUG-40584
}

void AutoGenerateAnswersEditorDialog::writeConfig()
{
    KConfigGroup group(KSharedConfig::openStateConfig(), QLatin1StringView(myAutoGenerateAnswersEditorDialogGroupName));
    KWindowConfig::saveWindowSize(windowHandle(), group);
}

#include "moc_autogenerateanswerseditordialog.cpp"
