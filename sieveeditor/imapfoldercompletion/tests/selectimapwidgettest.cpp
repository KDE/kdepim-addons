/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
