/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "confirmbeforedeletinginterface.h"
using namespace Qt::Literals::StringLiterals;

#include "confirmbeforedeletingmanager.h"
#include "confirmbeforedeletingmessageboxdialog.h"
#include "confirmbeforedeletingplugin_debug.h"
#include <KActionCollection>
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
        auto mainMenu = new QAction(i18nc("@action", "Confirm Before Deleting"), this);
        auto menu = new QMenu;
        auto act = new QAction(QIcon::fromTheme(u"settings-configure"_s), i18n("Configure"), menu);
        connect(act, &QAction::triggered, this, &ConfirmBeforeDeletingInterface::slotConfigure);
        ac->addAction(u"confirm_before_deleting_configure"_s, act);

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
                checkFoundStr = checkFoundStr.left(200) + u"…"_s;
            }
            dlg->setInfo(i18n("Do you want to delete this email?\n%1", checkFoundStr));
            const int result = dlg->exec();
            const auto button = static_cast<QDialogButtonBox::StandardButton>(result);
            if (button == QDialogButtonBox::StandardButton::Yes) {
                lst << item;
                if (dlg->useSameResult()) {
                    ruleDelete.append(std::move(r));
                }
            } else if (button == QDialogButtonBox::StandardButton::No) {
                if (dlg->useSameResult()) {
                    ruleNotDelete.append(std::move(r));
                }
            } else if (button == QDialogButtonBox::StandardButton::Cancel) {
                lst.clear();
                break;
            } else {
                lst.clear();
                break;
            }
            delete dlg;
        } else {
            lst << item;
        }
    }
    return lst;
}

#include "moc_confirmbeforedeletinginterface.cpp"
