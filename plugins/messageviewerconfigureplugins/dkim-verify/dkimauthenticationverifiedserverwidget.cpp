/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimauthenticationverifiedserverwidget.h"
#include <KLocalizedString>
#include <MessageViewer/DKIMManagerAuthenticationServer>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

DKIMAuthenticationVerifiedServerWidget::DKIMAuthenticationVerifiedServerWidget(QWidget *parent)
    : QWidget(parent)
    , mSelector(new DKIMAuthenticationVerifiedServerSelectorWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mSelector->setObjectName("mSelector"_L1);
    mainLayout->addWidget(mSelector);
}

DKIMAuthenticationVerifiedServerWidget::~DKIMAuthenticationVerifiedServerWidget() = default;

void DKIMAuthenticationVerifiedServerWidget::loadSettings()
{
    mSelector->setStringList(MessageViewer::DKIMManagerAuthenticationServer::self()->serverList());
}

void DKIMAuthenticationVerifiedServerWidget::saveSettings()
{
    const QStringList lst = mSelector->stringList();
    MessageViewer::DKIMManagerAuthenticationServer::self()->setServerList(lst);
}

DKIMAuthenticationVerifiedServerSelectorWidget::DKIMAuthenticationVerifiedServerSelectorWidget(QWidget *parent)
    : PimCommon::SimpleStringListEditor(parent)
{
    setAddDialogLabel(i18n("New Server:"));
    setAddDialogTitle(i18n("New Server"));
    setModifyDialogTitle(i18n("Modify Server"));
    setModifyDialogLabel(i18n("Server:"));
    setRemoveDialogLabel(i18n("Do you want to delete selected server(s) name?"));
}

DKIMAuthenticationVerifiedServerSelectorWidget::~DKIMAuthenticationVerifiedServerSelectorWidget() = default;

#include "moc_dkimauthenticationverifiedserverwidget.cpp"
