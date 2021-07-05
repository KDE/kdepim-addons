/*
   SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "confirmbeforedeletingwidget.h"
#include "confirmbeforedeletingcreateruledialog.h"
#include <KLocalizedString>
#include <QMenu>
#include <QTreeWidget>
#include <QVBoxLayout>

ConfirmBeforeDeletingWidget::ConfirmBeforeDeletingWidget(QWidget *parent)
    : QWidget(parent)
    , mTreeWidget(new QTreeWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins({});
    mainLayout->setObjectName(QStringLiteral("mainlayout"));
    // TODO
    mainLayout->addWidget(mTreeWidget);
    mTreeWidget->setAlternatingRowColors(true);
    mTreeWidget->setRootIsDecorated(false);
    mTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    const QStringList lst = {i18n("Name"), i18n("Type")};
    mTreeWidget->setHeaderLabels(lst);
    connect(mTreeWidget, &QTreeWidget::customContextMenuRequested, this, &ConfirmBeforeDeletingWidget::slotCustomContextMenuRequested);
}

ConfirmBeforeDeletingWidget::~ConfirmBeforeDeletingWidget()
{
}

void ConfirmBeforeDeletingWidget::slotCustomContextMenuRequested(const QPoint &p)
{
    QTreeWidgetItem *item = mTreeWidget->currentItem();
    if (!item) {
        return;
    }

    QMenu menu(this);
#if 0
    menu.addAction(QIcon::fromTheme(QStringLiteral("document-open")), i18n("Open"), this, &ConfirmBeforeDeletingWidget::slotOpenItem);
    if (filterValueIsNotEmpty) {
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Remove filter"), this, &ConfirmBeforeDeletingWidget::slotRemoveRule);
    }
#endif
    menu.exec(QCursor::pos());
}

void ConfirmBeforeDeletingWidget::slotRemoveRule()
{
    // TODO
}
