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

#include "adblockblockableitemswidget.h"

#include <QVBoxLayout>
#include <KLocalizedString>
#include <CustomTreeView>
#include <KTreeWidgetSearchLine>


AdBlockBlockableItemsWidget::AdBlockBlockableItemsWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *lay = new QVBoxLayout;
    lay->setMargin(0);
    setLayout(lay);
    mListItems = new PimCommon::CustomTreeView;
    mListItems->setDefaultText(i18n("No blockable element found."));

    mListItems->setContextMenuPolicy(Qt::CustomContextMenu);
    mListItems->setAlternatingRowColors(true);
    mListItems->setRootIsDecorated(false);
    //connect(mListItems, &PimCommon::CustomTreeView::customContextMenuRequested, this, &AdBlockBlockableItemsWidget::customContextMenuRequested);

    QStringList lst;
    lst << i18n("Filter") << i18n("Address") << i18n("Type");
    mListItems->setHeaderLabels(lst);

    KTreeWidgetSearchLine *searchLine = new KTreeWidgetSearchLine(this, mListItems);
    searchLine->setPlaceholderText(i18n("Search..."));

    lay->addWidget(searchLine);
    lay->addWidget(mListItems);

    //KConfigGroup config(MessageViewer::MessageViewerSettings::self()->config(), "AdBlockHeaders");
    //mListItems->header()->restoreState(config.readEntry("HeaderState", QByteArray()));
}

AdBlockBlockableItemsWidget::~AdBlockBlockableItemsWidget()
{
    //KConfigGroup groupHeader(MessageViewer::MessageViewerSettings::self()->config(), "AdBlockHeaders");
    //groupHeader.writeEntry("HeaderState", mListItems->header()->saveState());
    //groupHeader.sync();
}

