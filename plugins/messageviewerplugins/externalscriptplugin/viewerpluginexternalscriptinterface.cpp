/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "viewerpluginexternalscriptinterface.h"
#include "viewerpluginexternalscriptmanager.h"
#include "externalscriptplugin_debug.h"
#include "viewerpluginexternalscriptparseargument.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QAction>
#include <QDebug>
#include <QStandardPaths>
#include <QProcess>

#include <KActionCollection>
#include <KLocalizedString>
#include <KMessageBox>

using namespace MessageViewer;

ViewerPluginExternalscriptInterface::ViewerPluginExternalscriptInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    createAction(ac);
}

ViewerPluginExternalscriptInterface::~ViewerPluginExternalscriptInterface()
{

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
    mSelectedText = text;
}

void ViewerPluginExternalscriptInterface::execute()
{
    if (mCurrentInfo.count() == 2) {
        const QString executable = mCurrentInfo.at(1);
        const QString executablePath = QStandardPaths::findExecutable(executable);
        if (executablePath.isEmpty()) {
            KMessageBox::error(0, i18n("\'%1\' not found", executable), i18n("Executable not found."));
        } else {
            QProcess proc;
            const QStringList newCommandLine = mCurrentInfo.at(0).split(QLatin1Char(' '), QString::SkipEmptyParts);
            const QStringList splitArguments = adaptArguments(newCommandLine);
            if (!proc.startDetached(executablePath, splitArguments)) {
                KMessageBox::error(0, i18n("Impossible to start executable"));
            }
        }
    } else {
        qCDebug(EXTERNALSCRIPTPLUGIN_LOG) << "Problem with number of arguments " << mCurrentInfo.count();
    }
    clear();
}

void ViewerPluginExternalscriptInterface::clear()
{
    mSelectedText.clear();
    mCurrentInfo.clear();
    mMessage.clear();
}

void ViewerPluginExternalscriptInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        const QVector<ViewerPluginExternalScriptInfo> infos = ViewerPluginExternalScriptManager::self()->scriptInfos();
        if (!infos.isEmpty()) {
            QActionGroup *grp = new QActionGroup(this);
            connect(grp, &QActionGroup::triggered, this, &ViewerPluginExternalscriptInterface::slotScriptActivated);
            Q_FOREACH (ViewerPluginExternalScriptInfo info, infos) {
                QAction *act = new QAction(info.name(), this);
                act->setIconText(info.name());
                const QString &description = info.description();
                if (!description.isEmpty()) {
                    addHelpTextAction(act, description);
                }
                ac->addAction(QStringLiteral("externalscript_%1").arg(info.name()), act);
                QStringList actionInfo;
                actionInfo.append(info.commandLine());
                actionInfo.append(info.executable());

                act->setData(actionInfo);
                mAction.append(act);
                grp->addAction(act);
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
