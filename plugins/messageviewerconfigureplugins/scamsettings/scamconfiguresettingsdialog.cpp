/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "scamconfiguresettingsdialog.h"
#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QVBoxLayout>

ScamConfigureSettingsDialog::ScamConfigureSettingsDialog(QWidget *parent)
    : QDialog(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    setWindowTitle(i18nc("@title:window", "Configure Scam Settings"));
}

ScamConfigureSettingsDialog::~ScamConfigureSettingsDialog()
{
}
