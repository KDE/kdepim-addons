/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountpluginwidget.h"
#include <KLocalizedString>
#include <QTreeWidget>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;
CheckFolderSizeAccountPluginWidget::CheckFolderSizeAccountPluginWidget(QWidget *parent)
    : QWidget{parent}
    , mTreeWidget(new QTreeWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});

    // TODO a list of folder => show size (work only on imap and co)
    mTreeWidget->setObjectName(u"mTreeWidget"_s);
    mainLayout->addWidget(mTreeWidget);
}

CheckFolderSizeAccountPluginWidget::~CheckFolderSizeAccountPluginWidget() = default;

#include "moc_checkfoldersizeaccountpluginwidget.cpp"
