/*
   SPDX-FileCopyrightText: 2021-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "confirmbeforedeletinginterface.h"
#include "confirmbeforedeletingmanager.h"
#include "confirmbeforedeletingmessageboxdialog.h"
#include "confirmbeforedeletingplugin_debug.h"
#include <KLocalizedString>
#include <QAction>
#include <QDialogButtonBox>
#include <QIcon>
#include <QMenu>
#include <QPointer>

ConfirmBeforeDeletingInterface::ConfirmBeforeDeletingInterface(QObject *parent)
    : MessageViewer::MessageViewerCheckBeforeDeletingInterface(parent)
{
}

ConfirmBeforeDeletingInterface::~ConfirmBeforeDeletingInterface() = default;

QList<QAction *> ConfirmBeforeDeletingInterface::actions() const
{
    return mAction;
}

void ConfirmBeforeDeletingInterface::createActions(KActionCollection *ac)
{
    if (ac) {
        auto mainMenu = new QAction(i18n("Confirm Before Deleting"), this);
        auto menu = new QMenu;
        auto act = new QAction(QIcon::fromTheme(QStringLiteral("settings-configure")), i18n("Configure"), menu);
        connect(act, &QAction::triggered, this, &ConfirmBeforeDeletingInterface::slotConfigure);
        menu->addAction(act);
        mainMenu->setMenu(menu);
        mAction << mainMenu;
    }
}

void ConfirmBeforeDeletingInterface::slotConfigure()
{
    Q_EMIT configure(parentWidget());
}

Akonadi::Item::List ConfirmBeforeDeletingInterface::exec(const Akonadi::Item::List &list)
{
    Akonadi::Item::List lst;
    QString checkFoundStr;

    QList<ConfirmBeforeDeletingRule> ruleDelete;
    QList<ConfirmBeforeDeletingRule> ruleNotDelete;
    for (const auto &item : list) {
        ConfirmBeforeDeletingRule r;
        if (ConfirmBeforeDeletingManager::self()->deletingNeedToConfirm(item, checkFoundStr, r)) {
            if (ruleDelete.contains(r)) {
                lst << item;
                continue;
            }
            if (ruleNotDelete.contains(r)) {
                continue;
            }

            QPointer<ConfirmBeforeDeletingMessageBoxDialog> dlg = new ConfirmBeforeDeletingMessageBoxDialog(parentWidget());
            if (checkFoundStr.length() > 200) {
                checkFoundStr = checkFoundStr.left(200) + QStringLiteral("...");
            }
            dlg->setInfo(i18n("Do you want to delete this email?\n%1", checkFoundStr));
            const int result = dlg->exec();
            const auto button = static_cast<QDialogButtonBox::StandardButton>(result);
            if (button == QDialogButtonBox::StandardButton::Yes) {
                lst << item;
                if (dlg->useSameResult()) {
                    ruleDelete.append(r);
                }
                delete dlg;
            } else if (button == QDialogButtonBox::StandardButton::No) {
                if (dlg->useSameResult()) {
                    ruleNotDelete.append(r);
                }
                delete dlg;
            } else if (button == QDialogButtonBox::StandardButton::Cancel) {
                lst.clear();
                delete dlg;
                break;
            } else {
                qCWarning(KMAIL_CONFIRMBEFOREDELETING_PLUGIN_LOG) << " StandardButton is invalid " << button << " .It's a bug!";
            }
        } else {
            lst << item;
        }
    }
    return lst;
}

#include "moc_confirmbeforedeletinginterface.cpp"
