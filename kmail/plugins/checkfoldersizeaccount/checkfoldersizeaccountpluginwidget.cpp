/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountpluginwidget.h"
#include <KLocalizedString>
#include <QVBoxLayout>

CheckFolderSizeAccountPluginWidget::CheckFolderSizeAccountPluginWidget(QWidget *parent)
    : QWidget{parent}
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    // TODO a list of folder => show size (work only on imap and co)
}

CheckFolderSizeAccountPluginWidget::~CheckFolderSizeAccountPluginWidget() = default;

#include "moc_checkfoldersizeaccountpluginwidget.cpp"
