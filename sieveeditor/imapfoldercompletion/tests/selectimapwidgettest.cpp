/*
   Copyright (C) 2016-2020 Laurent Montel <montel@kde.org>

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

#include "selectimapwidgettest.h"
#include <KPluginLoader>
#include <QHBoxLayout>
#include <KPluginFactory>
#include <QDebug>
#include <QLabel>

SelectImapWidgetTest::SelectImapWidgetTest(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QStringLiteral("Test AbstractMoveImapFolderWidget plugin"));
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    KSieveUi::AbstractMoveImapFolderWidget *lineEdit = nullptr;
    KPluginLoader loader(QStringLiteral("libksieve/imapfoldercompletionplugin"));
    KPluginFactory *factory = loader.factory();
    if (factory) {
        lineEdit = factory->create<KSieveUi::AbstractMoveImapFolderWidget>();
    } else {
        lineEdit = new DefaultMoveImapFolderWidget(this);
        qDebug() << " error during load : " << loader.errorString();
    }
    mainLayout->addWidget(lineEdit);
}

SelectImapWidgetTest::~SelectImapWidgetTest()
{
}

DefaultMoveImapFolderWidget::DefaultMoveImapFolderWidget(QWidget *parent)
    : KSieveUi::AbstractMoveImapFolderWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QLabel *label = new QLabel(QStringLiteral("Problem during loading plugin! Please verify your installation."));
    mainLayout->addWidget(label);
}

void DefaultMoveImapFolderWidget::setText(const QString &str)
{
    Q_UNUSED(str);
}

QString DefaultMoveImapFolderWidget::text() const
{
    return {};
}

void DefaultMoveImapFolderWidget::setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account)
{
    Q_UNUSED(account);
}
