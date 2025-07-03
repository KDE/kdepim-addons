/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountpluginconfigurewidget.h"
#include <KLocalizedString>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
CheckFolderSizeAccountPluginConfigureWidget::CheckFolderSizeAccountPluginConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mWarningSpinBox(new QSpinBox(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins({});
    mainLayout->addWidget(new QLabel(i18nc("@label:textbox", "Display Colored Folder when size is too expensive."), this));
    auto hboxLayout = new QHBoxLayout;
    hboxLayout->setContentsMargins({});
    hboxLayout->setObjectName(u"hboxLayout"_s);
    mainLayout->addLayout(hboxLayout);

    // TODO add size
    hboxLayout->addWidget(new QLabel(i18nc("@label:textbox", "Size:"), this));
    hboxLayout->addWidget(mWarningSpinBox);
    load();
}

CheckFolderSizeAccountPluginConfigureWidget::~CheckFolderSizeAccountPluginConfigureWidget() = default;

void CheckFolderSizeAccountPluginConfigureWidget::load()
{
}

void CheckFolderSizeAccountPluginConfigureWidget::save()
{
}

#include "moc_checkfoldersizeaccountpluginconfigurewidget.cpp"
