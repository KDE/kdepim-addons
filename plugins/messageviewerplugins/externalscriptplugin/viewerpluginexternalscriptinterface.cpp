/*
   Copyright (C) 2016-2018 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/
#include "viewerpluginexternalscriptinterface.h"
#include "viewerpluginexternalscriptmanager.h"
#include "externalscriptplugin_debug.h"
#include "viewerpluginexternalscriptparseargument.h"

#include <QIcon>
#include <QAction>
#include <QStandardPaths>
#include <QProcess>

#include <KActionCollection>
#include <KLocalizedString>
#include <KMessageBox>

using namespace MessageViewer;

ViewerPluginExternalscriptInterface::ViewerPluginExternalscriptInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    mActionGroup = new QActionGroup(this);
    createAction(ac);
}

ViewerPluginExternalscriptInterface::~ViewerPluginExternalscriptInterface()
{
}

void ViewerPluginExternalscriptInterface::refreshActionList(KActionCollection *ac)
{
    ViewerPluginExternalScriptManager::self()->readExternalScriptInfo();
    delete mActionGroup;
    for (QAction *act : qAsConst(mAction)) {
        ac->removeAction(act);
    }
    mAction.clear();
    mActionGroup = new QActionGroup(this);
    createAction(ac);
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
            KMessageBox::error(nullptr, i18n("\'%1\' not found", executable), i18n("Executable not found."));
        } else {
            QProcess proc;
            const QStringList newCommandLine = mCurrentInfo.at(0).split(QLatin1Char(' '), QString::SkipEmptyParts);
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
        const QVector<ViewerPluginExternalScriptInfo> infos = ViewerPluginExternalScriptManager::self()->scriptInfos();
        if (!infos.isEmpty()) {
            connect(mActionGroup, &QActionGroup::triggered, this, &ViewerPluginExternalscriptInterface::slotScriptActivated);
            for (const ViewerPluginExternalScriptInfo &info : infos) {
                QAction *act = new QAction(info.name(), this);
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
                const QStringList actionInfo {
                    info.commandLine(), info.executable()
                };

                act->setData(actionInfo);
                mAction.append(act);
                mActionGroup->addAction(act);
            }
        }
    }
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
    return parser.parse(scriptArguments);
}
