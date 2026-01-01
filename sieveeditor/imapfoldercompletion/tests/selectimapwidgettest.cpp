/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "selectimapwidgettest.h"
#include <KPluginFactory>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>

SelectImapWidgetTest::SelectImapWidgetTest(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QStringLiteral("Test AbstractMoveImapFolderWidget plugin"));
    auto mainLayout = new QHBoxLayout(this);

    KSieveUi::AbstractMoveImapFolderWidget *lineEdit = nullptr;
    const KPluginMetaData editWidgetPlugin(QStringLiteral("pim6/libksieve/imapfoldercompletionplugin"));

    const auto result = KPluginFactory::instantiatePlugin<KSieveUi::AbstractMoveImapFolderWidget>(editWidgetPlugin);
    if (result) {
        lineEdit = result.plugin;
    } else {
        lineEdit = new DefaultMoveImapFolderWidget(this);
        // qDebug() << " error during load : " << loader.errorString();
    }
    mainLayout->addWidget(lineEdit);
}

SelectImapWidgetTest::~SelectImapWidgetTest() = default;

DefaultMoveImapFolderWidget::DefaultMoveImapFolderWidget(QWidget *parent)
    : KSieveUi::AbstractMoveImapFolderWidget(parent)
{
    auto mainLayout = new QHBoxLayout(this);
    auto label = new QLabel(QStringLiteral("Problem during loading plugin! Please verify your installation."));
    mainLayout->addWidget(label);
}

void DefaultMoveImapFolderWidget::setText(const QString &str)
{
    Q_UNUSED(str)
}

QString DefaultMoveImapFolderWidget::text() const
{
    return {};
}

void DefaultMoveImapFolderWidget::setSieveImapAccountSettings(const KSieveCore::SieveImapAccountSettings &account)
{
    Q_UNUSED(account)
}

#include "moc_selectimapwidgettest.cpp"
