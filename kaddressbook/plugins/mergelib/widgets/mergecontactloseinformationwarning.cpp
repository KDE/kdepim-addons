/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactloseinformationwarning.h"
#include <KLocalizedString>
#include <QAction>

using namespace KABMergeContacts;
MergeContactLoseInformationWarning::MergeContactLoseInformationWarning(QWidget *parent)
    : KMessageWidget(parent)
{
    setVisible(false);
    setCloseButtonVisible(false);
    setMessageType(Information);
    setWordWrap(true);

    setText(i18n("Some information can be lost. Do you want to continue, or customize what you want to merge?"));

    QAction *action = new QAction(i18n("Customize"), this);
    action->setObjectName(QStringLiteral("customize"));
    connect(action, &QAction::triggered, this, &MergeContactLoseInformationWarning::slotCustomizeMerge);
    addAction(action);

    action = new QAction(i18n("Automatic Merging"), this);
    action->setObjectName(QStringLiteral("automatic"));
    connect(action, &QAction::triggered, this, &MergeContactLoseInformationWarning::slotAutomaticMerging);
    addAction(action);
}

MergeContactLoseInformationWarning::~MergeContactLoseInformationWarning()
{
}

void MergeContactLoseInformationWarning::slotCustomizeMerge()
{
    animatedHide();
    Q_EMIT customizeMergingContacts();
}

void MergeContactLoseInformationWarning::slotAutomaticMerging()
{
    animatedHide();
    Q_EMIT continueMerging();
}
