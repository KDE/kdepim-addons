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

#include <KActionCollection>
#include <KLocalizedString>

using namespace MessageViewer;

ViewerPluginExternalscriptInterface::ViewerPluginExternalscriptInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    //TODO
    createAction(ac);
}

ViewerPluginExternalscriptInterface::~ViewerPluginExternalscriptInterface()
{

}

QList<QAction *> ViewerPluginExternalscriptInterface::actions() const
{
    return mAction;
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginExternalscriptInterface::featureTypes() const
{
    return NeedMessage;
}

void ViewerPluginExternalscriptInterface::execute()
{
    //TODO
}

void ViewerPluginExternalscriptInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        const QVector<ViewerPluginExternalScriptInfo> infos = ViewerPluginExternalScriptManager::self()->scriptInfos();
        Q_FOREACH (ViewerPluginExternalScriptInfo info, infos) {
            QAction *act = new QAction(QIcon::fromTheme(QStringLiteral("task-new")), i18n("Create Todo"), this);
            act->setIconText(info.name());
            const QString &description = info.description();
            if (!description.isEmpty()) {
                addHelpTextAction(act, description);
            }
            //TODO create uniq value for kactioncollection
            ac->addAction(QStringLiteral("create_todo"), act);
            //connect(act, &QAction::triggered, this, &ViewerPluginCreateTodoInterface::slotActivatePlugin);
            mAction.append(act);
        }
    }
}
