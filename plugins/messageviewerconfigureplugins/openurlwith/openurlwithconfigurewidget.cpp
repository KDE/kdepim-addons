/*
   SPDX-FileCopyrightText: 2022 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurewidget.h"
#include "openurlwithconfigurecreatedialog.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QHeaderView>
#include <QMenu>
#include <QTreeWidget>
#include <QVBoxLayout>

OpenUrlWithConfigureWidget::OpenUrlWithConfigureWidget(QWidget *parent)
    : QWidget{parent}
    , mTreeWidget(new QTreeWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins());

    mTreeWidget->setObjectName(QStringLiteral("mTreeWidget"));
    mainLayout->addWidget(mTreeWidget);
    mTreeWidget->setRootIsDecorated(false);
    mTreeWidget->header()->setSectionsMovable(false);
    mTreeWidget->setHeaderLabels({i18n("Domain"), i18n("Command Line")});
    mTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    mTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mTreeWidget->header()->setSortIndicatorShown(true);
    mTreeWidget->setSortingEnabled(true);
    connect(mTreeWidget, &QTreeWidget::customContextMenuRequested, this, &OpenUrlWithConfigureWidget::slotCustomContextMenuRequested);
    connect(mTreeWidget, &QTreeWidget::itemDoubleClicked, this, &OpenUrlWithConfigureWidget::slotEditRule);
}

OpenUrlWithConfigureWidget::~OpenUrlWithConfigureWidget()
{
}

void OpenUrlWithConfigureWidget::loadSettings()
{
    // TODO
}

void OpenUrlWithConfigureWidget::writeSettings()
{
    // TODO
}

void OpenUrlWithConfigureWidget::slotAddRule()
{
    // TODO
}

void OpenUrlWithConfigureWidget::slotEditRule()
{
    // TODO
}

void OpenUrlWithConfigureWidget::slotRemoveRule()
{
    auto items = mTreeWidget->selectedItems();
    if (!items.isEmpty()) {
        const int answer = KMessageBox::questionYesNo(this,
                                                      i18np("Do you want to remove this rule?", "Do you want to remove these rules?", items.count()),
                                                      i18nc("@title", "Remove Rule"),
                                                      KStandardGuiItem::remove(),
                                                      KStandardGuiItem::cancel());

        if (answer == KMessageBox::Yes) {
            while (!items.isEmpty()) {
                delete items.takeFirst();
            }
        }
    }
}

void OpenUrlWithConfigureWidget::slotCustomContextMenuRequested(const QPoint &p)
{
    QMenu menu(this);
    const int selectedItemCount{mTreeWidget->selectedItems().count()};
    menu.addAction(QIcon::fromTheme(QStringLiteral("list-add")), i18n("Add Rule..."), this, &OpenUrlWithConfigureWidget::slotAddRule);
    if (selectedItemCount == 1) {
        menu.addAction(QIcon::fromTheme(QStringLiteral("document-edit")), i18n("Edit Rule..."), this, &OpenUrlWithConfigureWidget::slotEditRule);
    }
    if (selectedItemCount > 0) {
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("list-remove")),
                       i18np("Remove Rule", "Remove Rules", selectedItemCount),
                       this,
                       &OpenUrlWithConfigureWidget::slotRemoveRule);
    }
    menu.exec(QCursor::pos());
}
