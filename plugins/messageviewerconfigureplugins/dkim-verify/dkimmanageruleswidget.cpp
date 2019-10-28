/*
   Copyright (C) 2019 Laurent Montel <montel@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "dkimmanageruleswidget.h"
#include <MessageViewer/DKIMManagerRules>
#include <QVBoxLayout>
#include <KLocalizedString>
#include <QTreeWidget>
#include <KTreeWidgetSearchLine>
#include <QMenu>

DKIMManageRulesWidget::DKIMManageRulesWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mTreeWidget = new QTreeWidget(this);
    mTreeWidget->setObjectName(QStringLiteral("treewidget"));
    mTreeWidget->setRootIsDecorated(false);
    mTreeWidget->setHeaderLabels({i18n("Domain"), i18n("List-ID"), i18n("From"), i18n("SDID"), i18n("Rule type")});
    mTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    mTreeWidget->setAlternatingRowColors(true);

    KTreeWidgetSearchLine *searchLineEdit = new KTreeWidgetSearchLine(this, mTreeWidget);
    searchLineEdit->setObjectName(QStringLiteral("searchlineedit"));
    searchLineEdit->setClearButtonEnabled(true);
    mainLayout->addWidget(searchLineEdit);

    mainLayout->addWidget(mTreeWidget);
    connect(mTreeWidget, &QTreeWidget::customContextMenuRequested, this, &DKIMManageRulesWidget::customContextMenuRequested);
}

DKIMManageRulesWidget::~DKIMManageRulesWidget()
{
}

void DKIMManageRulesWidget::loadSettings()
{
    const QVector<MessageViewer::DKIMRule> rules = MessageViewer::DKIMManagerRules::self()->rules();
    //TODO
}

void DKIMManageRulesWidget::saveSettings()
{
    //TODO
}

void DKIMManageRulesWidget::customContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QTreeWidgetItem *item = mTreeWidget->currentItem();
    QMenu menu(this);
    if (item) {
        menu.addAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Add..."), this, [this, item]() {
            //TODO
        });
        menu.addAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18n("Modify..."), this, [this, item]() {
            //TODO
        });
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Remove Rule"), this, [this, item]() {
            delete item;
        });
        menu.addSeparator();
    }
    menu.addAction(i18n("Delete All"), this, [this]() {
        mTreeWidget->clear();
    });
    menu.exec(QCursor::pos());
}
