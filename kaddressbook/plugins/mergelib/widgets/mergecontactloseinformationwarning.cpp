/*
   SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>

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

    auto action = new QAction(i18n("Customize"), this);
    action->setObjectName(QLatin1StringView("customize"));
    connect(action, &QAction::triggered, this, &MergeContactLoseInformationWarning::slotCustomizeMerge);
    addAction(action);

    action = new QAction(i18n("Automatic Merging"), this);
    action->setObjectName(QLatin1StringView("automatic"));
    connect(action, &QAction::triggered, this, &MergeContactLoseInformationWarning::slotAutomaticMerging);
    addAction(action);
}

MergeContactLoseInformationWarning::~MergeContactLoseInformationWarning() = default;

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

#include "moc_mergecontactloseinformationwarning.cpp"
