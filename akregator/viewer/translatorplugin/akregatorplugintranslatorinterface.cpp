/*
  Copyright (c) 2015-2016 Montel Laurent <montel@kde.org>

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

#include "akregatorplugintranslatorinterface.h"
#include "pimcommon/translatorwidget.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QAction>

#include <KActionCollection>
#include <KLocalizedString>

using namespace MessageViewer;

AkregatorPluginTranslatorInterface::AkregatorPluginTranslatorInterface(KActionCollection *ac, QWidget *parent)
    : ViewerPluginInterface(parent),
      mAction(Q_NULLPTR)
{
    mTranslatorWidget = new PimCommon::TranslatorWidget(parent);
    mTranslatorWidget->setObjectName(QStringLiteral("translatorwidget"));
    parent->layout()->addWidget(mTranslatorWidget);
    createAction(ac);
}

AkregatorPluginTranslatorInterface::~AkregatorPluginTranslatorInterface()
{

}

void AkregatorPluginTranslatorInterface::setText(const QString &text)
{
    mTranslatorWidget->setTextToTranslate(text);
}

QAction *AkregatorPluginTranslatorInterface::action() const
{
    return mAction;
}

void AkregatorPluginTranslatorInterface::showWidget()
{
    mTranslatorWidget->show();
}

ViewerPluginInterface::SpecificFeatureTypes AkregatorPluginTranslatorInterface::featureTypes() const
{
    return NeedSelection;
}

void AkregatorPluginTranslatorInterface::createAction(KActionCollection *ac)
{
    if (ac) {
        mAction = new QAction(i18n("Translate..."), this);
        ac->setDefaultShortcut(mAction, QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_T));
        mAction->setIcon(QIcon::fromTheme(QStringLiteral("preferences-desktop-locale")));
        ac->addAction(QStringLiteral("translate_text"), mAction);
        connect(mAction, &QAction::triggered, this, &AkregatorPluginTranslatorInterface::slotActivatePlugin);
    }
}
