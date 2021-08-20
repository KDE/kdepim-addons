/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "confirmbeforedeletinginterface.h"
#include "confirmbeforedeletingmanager.h"
#include "confirmbeforedeletingmessageboxdialog.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QAction>
#include <QIcon>
#include <QMenu>
#include <QPointer>

ConfirmBeforeDeletingInterface::ConfirmBeforeDeletingInterface(QObject *parent)
    : MessageViewer::MessageViewerCheckBeforeDeletingInterface(parent)
{
}

ConfirmBeforeDeletingInterface::~ConfirmBeforeDeletingInterface()
{
}

QList<QAction *> ConfirmBeforeDeletingInterface::actions() const
{
    return mAction;
}

void ConfirmBeforeDeletingInterface::createActions(KActionCollection *ac)
{
    // TODO
    if (ac) {
        auto mainMenu = new QAction(i18n("External Script"), this);
        auto menu = new QMenu;
        auto act = new QAction(QIcon::fromTheme(QStringLiteral("settings-configure")), i18n("Configure"), menu);
        // TODO connect(act, &QAction::triggered, this, &ConfirmBeforeDeletingInterface::slotConfigure);
        menu->addAction(act);
        mainMenu->setMenu(menu);
        mAction << mainMenu;
    }
}

Akonadi::Item::List ConfirmBeforeDeletingInterface::exec(const Akonadi::Item::List &list)
{
    Akonadi::Item::List lst;
    QString checkFoundStr;

    QVector<ConfirmBeforeDeletingRule> ruleDelete;
    QVector<ConfirmBeforeDeletingRule> ruleNotDelete;
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
                qWarning() << " StandardButton is invalid " << button << " .It's a bug!";
            }
        } else {
            lst << item;
        }
    }
    return lst;
}
