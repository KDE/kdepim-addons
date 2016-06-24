/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

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

#include "viewerplugintranslatorinterface.h"
#include "pimcommon/translatorwidget.h"

#include <QIcon>
#include <QAction>
#include <QLayout>
#include <KActionCollection>
#include <KLocalizedString>

using namespace MessageViewer;

ViewerPluginTranslatorInterface::ViewerPluginTranslatorInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent)
{
    mTranslatorWidget = new PimCommon::TranslatorWidget(parent);
    mTranslatorWidget->setObjectName(QStringLiteral("translatorwidget"));
    parent->layout()->addWidget(mTranslatorWidget);
    createAction(ac);
}

ViewerPluginTranslatorInterface::~ViewerPluginTranslatorInterface()
{

}

void ViewerPluginTranslatorInterface::setText(const QString &text)
{
    mTranslatorWidget->setTextToTranslate(text);
}

QList<QAction *> ViewerPluginTranslatorInterface::actions() const
{
    return mAction;
}

void ViewerPluginTranslatorInterface::showWidget()
{
    mTranslatorWidget->show();
}

ViewerPluginInterface::SpecificFeatureTypes ViewerPluginTranslatorInterface::featureTypes() const
{
    return NeedSelection;
}

void ViewerPluginTranslatorInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        QAction *act = new QAction(i18n("Translate..."), this);
        ac->setDefaultShortcut(act, QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_T));
        act->setIcon(QIcon::fromTheme(QStringLiteral("preferences-desktop-locale")));
        ac->addAction(QStringLiteral("translate_text"), act);
        connect(act, &QAction::triggered, this, &ViewerPluginTranslatorInterface::slotActivatePlugin);
        mAction.append(act);
    }
}
