/*
   Copyright (C) 2019-2020 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
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
    mainLayout->setContentsMargins(0, 0, 0, 0);

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
