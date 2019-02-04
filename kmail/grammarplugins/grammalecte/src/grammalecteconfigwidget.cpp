/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

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

#include "grammalecteconfigwidget.h"
#include "grammalectegenerateconfigoptionjob.h"
#include <QVBoxLayout>
#include <QTabWidget>
#include <KLocalizedString>
#include <KConfigGroup>
#include <KSharedConfig>

GrammalecteConfigWidget::GrammalecteConfigWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    mainLayout->setMargin(0);

    QTabWidget *mTab = new QTabWidget(this);
    mTab->setObjectName(QStringLiteral("mTab"));
    mainLayout->addWidget(mTab);
    mTab->addTab(addGeneralTab(), i18n("General"));
    mTab->addTab(addGrammarTab(), i18n("Grammar Settings"));
}

GrammalecteConfigWidget::~GrammalecteConfigWidget()
{

}

QWidget *GrammalecteConfigWidget::addGrammarTab()
{
    QWidget *w = new QWidget(this);
    w->setObjectName(QStringLiteral("grammar"));
    return w;
}

QWidget *GrammalecteConfigWidget::addGeneralTab()
{
    QWidget *w = new QWidget(this);
    w->setObjectName(QStringLiteral("general"));
    return w;
}

void GrammalecteConfigWidget::loadSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Grammalecte");
    //TODO
}

void GrammalecteConfigWidget::saveSettings()
{
    KConfigGroup grp(KSharedConfig::openConfig(), "Grammalecte");
    //TODO
}
