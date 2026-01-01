/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "checkfoldersizeaccountpluginconfigurewidget.h"
#include "checkfoldersizeaccount.h"
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

    hboxLayout->addWidget(new QLabel(i18nc("@label:textbox", "Size:"), this));
    mWarningSpinBox->setMaximum(999999999);
    mWarningSpinBox->setSingleStep(100000);
    hboxLayout->addWidget(mWarningSpinBox);
    load();
}

CheckFolderSizeAccountPluginConfigureWidget::~CheckFolderSizeAccountPluginConfigureWidget() = default;

void CheckFolderSizeAccountPluginConfigureWidget::load()
{
    mWarningSpinBox->setValue(CheckFolderSizeAccountSettings::self()->warningSize());
}

void CheckFolderSizeAccountPluginConfigureWidget::save()
{
    CheckFolderSizeAccountSettings::self()->setWarningSize(mWarningSpinBox->value());
}

#include "moc_checkfoldersizeaccountpluginconfigurewidget.cpp"
