/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "dkimauthenticationverifiedserverwidget.h"
#include <QVBoxLayout>
#include <KLocalizedString>
#include <MessageViewer/DKIMManagerAuthenticationServer>

DKIMAuthenticationVerifiedServerWidget::DKIMAuthenticationVerifiedServerWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins({});

    mSelector = new DKIMAuthenticationVerifiedServerSelectorWidget(this);
    mSelector->setObjectName(QStringLiteral("mSelector"));
    mainLayout->addWidget(mSelector);
}

DKIMAuthenticationVerifiedServerWidget::~DKIMAuthenticationVerifiedServerWidget()
{
}

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
    setAddDialogLabel(i18n("New Server"));
    setRemoveDialogLabel(i18n("Do you want to delete selected server name?"));
}

DKIMAuthenticationVerifiedServerSelectorWidget::~DKIMAuthenticationVerifiedServerSelectorWidget()
{
}
