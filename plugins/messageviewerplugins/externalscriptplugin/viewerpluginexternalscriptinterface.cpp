/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "viewerpluginexternalscriptinterface.h"
#include "externalscriptplugin_debug.h"
#include "viewerpluginexternalscriptmanager.h"
#include "viewerpluginexternalscriptparseargument.h"

#include <QAction>
#include <QActionGroup>
#include <QIcon>
#include <QPointer>
#include <QProcess>
#include <QStandardPaths>

#include <KActionCollection>
#include <KLocalizedString>
#include <KMessageBox>
#include <QMenu>

#include <configuredialog/viewerpluginexternalconfiguredialog.h>

using namespace MessageViewer;

ViewerPluginExternalscriptInterface::ViewerPluginExternalscriptInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
    , mActionGroup(new QActionGroup(this))
{
    createAction(ac);
}

ViewerPluginExternalscriptInterface::~ViewerPluginExternalscriptInterface() = default;

void ViewerPluginExternalscriptInterface::refreshActionList(KActionCollection *ac)
{
    ViewerPluginExternalScriptManager::self()->readExternalScriptInfo();
    delete mActionGroup;
    for (QAction *act : std::as_const(mAction)) {
        ac->removeAction(act);
    }
    mAction.clear();
    mActionGroup = new QActionGroup(this);
    createAction(ac);
}

void ViewerPluginExternalscriptInterface::setMessageItem(const Akonadi::Item &item)
{
    mAkonadiUrl = item.url(Akonadi::Item::UrlWithMimeType).toString();
}

void ViewerPluginExternalscriptInterface::setMessage(const KMime::Message::Ptr &msg)
{
    mMessage = msg;
}

QList<QAction *> ViewerPluginExternalscriptInterface::actions() const
{
    return mAction;
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginExternalscriptInterface::featureTypes() const
{
    return NeedMessage;
}

void ViewerPluginExternalscriptInterface::setText(const QString &text)
{
    mText = text;
}

void ViewerPluginExternalscriptInterface::execute()
{
    if (mCurrentInfo.count() == 2) {
        const QString executable = mCurrentInfo.at(1);
        const QString executablePath = QStandardPaths::findExecutable(executable);
        if (executablePath.isEmpty()) {
            KMessageBox::error(nullptr, i18n("\'%1\' not found", executable), i18nc("@title:window", "Executable not found."));
        } else {
            QProcess proc;
            const QStringList newCommandLine = mCurrentInfo.at(0).split(QLatin1Char(' '), Qt::SkipEmptyParts);
            const QStringList splitArguments = adaptArguments(newCommandLine);
            if (!proc.startDetached(executablePath, splitArguments)) {
                KMessageBox::error(nullptr, i18n("Impossible to start executable"));
            }
        }
    } else {
        qCDebug(EXTERNALSCRIPTPLUGIN_LOG) << "Problem with number of arguments " << mCurrentInfo.count();
    }
    clear();
}

void ViewerPluginExternalscriptInterface::clear()
{
    mText.clear();
    mCurrentInfo.clear();
    mMessage.clear();
}

void ViewerPluginExternalscriptInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        auto mainMenu = new QAction(i18n("External Script"), this);
        const QList<ViewerPluginExternalScriptInfo> infos = ViewerPluginExternalScriptManager::self()->scriptInfos();
        auto menu = new QMenu;
        if (!infos.isEmpty()) {
            connect(mActionGroup, &QActionGroup::triggered, this, &ViewerPluginExternalscriptInterface::slotScriptActivated);
            for (const ViewerPluginExternalScriptInfo &info : infos) {
                auto act = new QAction(info.name(), menu);
                act->setIconText(info.name());
                const QString &description = info.description();
                if (!description.isEmpty()) {
                    addHelpTextAction(act, description);
                }
                const QString &icon = info.icon();
                if (!icon.isEmpty()) {
                    act->setIcon(QIcon::fromTheme(icon));
                }
                ac->addAction(QStringLiteral("externalscript_%1").arg(info.name()), act);
                const QStringList actionInfo{info.commandLine(), info.executable()};

                act->setData(actionInfo);
                menu->addAction(act);
                mActionGroup->addAction(act);
            }
            menu->addSeparator();
        }
        auto act = new QAction(QIcon::fromTheme(QStringLiteral("settings-configure")), i18n("Configure"), menu);
        connect(act, &QAction::triggered, this, &ViewerPluginExternalscriptInterface::slotConfigure);
        menu->addAction(act);
        mainMenu->setMenu(menu);
        act = new QAction(menu);
        act->setSeparator(true);
        mAction << mainMenu << act;
    }
}

void ViewerPluginExternalscriptInterface::slotConfigure()
{
    QPointer<ViewerPluginExternalConfigureDialog> dlg = new ViewerPluginExternalConfigureDialog;
    if (dlg->exec()) {
        Q_EMIT configChanged();
    }
    delete dlg;
}

void ViewerPluginExternalscriptInterface::slotScriptActivated(QAction *act)
{
    mCurrentInfo = act->data().toStringList();
    slotActivatePlugin();
}

QStringList ViewerPluginExternalscriptInterface::adaptArguments(const QStringList &scriptArguments)
{
    ViewerPluginExternalScriptParseArgument parser;
    parser.setMessage(mMessage);
    parser.setAkonadiUrl(mAkonadiUrl);
    return parser.parse(scriptArguments);
}

#include "moc_viewerpluginexternalscriptinterface.cpp"
