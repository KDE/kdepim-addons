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

#include <QHBoxLayout>
#include <QIcon>
#include <QAction>
#include <QDebug>

#include <KActionCollection>
#include <KLocalizedString>

using namespace MessageViewer;

ViewerPluginExternalscriptInterface::ViewerPluginExternalscriptInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    createAction(ac);
}

ViewerPluginExternalscriptInterface::~ViewerPluginExternalscriptInterface()
{

}

void ViewerPluginExternalscriptInterface::setMessage(const KMime::Message::Ptr &value)
{
    //TODO
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
        //TODO
    } else {
        qDebug() << "Problem with arguments";
    }
    //TODO clear();
}

void ViewerPluginExternalscriptInterface::clear()
{
    mSelectedText.clear();
    mCurrentInfo.clear();
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
                //TODO adapt command line
                actionInfo.append(info.commandLine());
                actionInfo.append(info.executable());

                act->setData(actionInfo);
                //TODO add info.
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

QString ViewerPluginExternalscriptInterface::adaptArguments(const QString &scriptArguments)
{
    //TODO
    return {};
}
