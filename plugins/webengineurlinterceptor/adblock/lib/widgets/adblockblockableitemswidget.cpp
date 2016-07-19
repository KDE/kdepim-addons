/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#include "adblockblockableitemswidget.h"
#include "adblockcreatefilterdialog.h"
#include "adblockinterceptor_debug.h"
#include <WebEngineViewer/WebEngineScript>

#include <QVBoxLayout>
#include <KLocalizedString>
#include <CustomTreeView>
#include <KTreeWidgetSearchLine>
#include <KConfigGroup>
#include <KSharedConfig>
#include <QHeaderView>
#include <QWebEngineView>
#include <QMenu>
#include <QClipboard>
#include <QApplication>
#include <QPointer>
#include <adblockblockableitemsjob.h>
#include <KIOWidgets/KRun>
using namespace AdBlock;

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
    connect(mListItems, &PimCommon::CustomTreeView::customContextMenuRequested, this, &AdBlockBlockableItemsWidget::customContextMenuRequested);

    QStringList lst;
    lst << i18n("Filter") << i18n("Address") << i18n("Type");
    mListItems->setHeaderLabels(lst);

    KTreeWidgetSearchLine *searchLine = new KTreeWidgetSearchLine(this, mListItems);
    searchLine->setPlaceholderText(i18n("Search..."));

    lay->addWidget(searchLine);
    lay->addWidget(mListItems);

    readConfig();
}

AdBlockBlockableItemsWidget::~AdBlockBlockableItemsWidget()
{
    writeConfig();
}

void AdBlockBlockableItemsWidget::setAdblockResult(const QVector<AdBlockResult> &result)
{
    Q_FOREACH (const AdBlockResult &res, result) {
        QTreeWidgetItem *item = new QTreeWidgetItem(mListItems);
        item->setText(Url, res.src);
        switch (res.type) {
        case AdBlock::AdBlockBlockableItemsJob::UnKnown:
            //TODO ?
            break;
        case AdBlock::AdBlockBlockableItemsJob::Image:
            item->setText(Type, elementTypeToI18n(AdBlockBlockableItemsWidget::Image));
            item->setData(Type, Element, Image);
            break;
        case AdBlock::AdBlockBlockableItemsJob::Script:
            item->setText(Type, elementTypeToI18n(AdBlockBlockableItemsWidget::Script));
            item->setData(Type, Element, Script);
            break;
        }
        item->setTextColor(FilterValue, Qt::red);
    }
    mListItems->setShowDefaultText(mListItems->model()->rowCount() == 0);
}

void AdBlockBlockableItemsWidget::customContextMenuRequested(const QPoint &)
{
    QTreeWidgetItem *item = mListItems->currentItem();
    if (!item) {
        return;
    }

    QMenu menu;
    menu.addAction(QIcon::fromTheme(QStringLiteral("edit-copy")), i18n("Copy url"), this, &AdBlockBlockableItemsWidget::slotCopyItem);
    const bool filterValueIsNotEmpty = !item->text(FilterValue).isEmpty();
    if (filterValueIsNotEmpty) {
        menu.addAction(QIcon::fromTheme(QStringLiteral("edit-copy")), i18n("Copy filter"), this, &AdBlockBlockableItemsWidget::slotCopyFilterItem);
    }
    menu.addAction(i18n("Block item..."), this, &AdBlockBlockableItemsWidget::slotBlockItem);
    menu.addSeparator();
    menu.addAction(QIcon::fromTheme(QStringLiteral("document-open")), i18n("Open"), this, &AdBlockBlockableItemsWidget::slotOpenItem);
    if (filterValueIsNotEmpty) {
        menu.addSeparator();
        menu.addAction(QIcon::fromTheme(QStringLiteral("edit-delete")), i18n("Remove filter"), this, &AdBlockBlockableItemsWidget::slotRemoveFilter);
    }
    menu.exec(QCursor::pos());
}

void AdBlockBlockableItemsWidget::writeConfig()
{
    KConfigGroup groupHeader(KSharedConfig::openConfig(), "AdBlockHeaders");
    groupHeader.writeEntry("HeaderState", mListItems->header()->saveState());
    groupHeader.sync();
}

void AdBlockBlockableItemsWidget::readConfig()
{
    KConfigGroup config(KSharedConfig::openConfig(), "AdBlockHeaders");
    mListItems->header()->restoreState(config.readEntry("HeaderState", QByteArray()));
}

void AdBlockBlockableItemsWidget::slotCopyFilterItem()
{
    QTreeWidgetItem *item = mListItems->currentItem();
    if (!item) {
        return;
    }
    QClipboard *cb = QApplication::clipboard();
    cb->setText(item->text(FilterValue), QClipboard::Clipboard);
}

void AdBlockBlockableItemsWidget::slotOpenItem()
{
    QTreeWidgetItem *item = mListItems->currentItem();
    if (!item) {
        return;
    }
    const QUrl url(item->text(Url));
    KRun *runner = new KRun(url, this);   // will delete itself
    runner->setRunExecutables(false);
}

void AdBlockBlockableItemsWidget::slotBlockItem()
{
    QTreeWidgetItem *item = mListItems->currentItem();
    if (!item) {
        return;
    }
    QPointer<AdBlockCreateFilterDialog> dlg = new AdBlockCreateFilterDialog(this);
    dlg->setPattern(static_cast<TypeElement>(item->data(Type, Element).toInt()), item->text(Url));
    if (dlg->exec()) {
        const QString filter = dlg->filter();
        item->setText(FilterValue, filter);
    }
    delete dlg;
}

void AdBlockBlockableItemsWidget::slotCopyItem()
{
    QTreeWidgetItem *item = mListItems->currentItem();
    if (!item) {
        return;
    }
    QClipboard *cb = QApplication::clipboard();
    cb->setText(item->text(Url), QClipboard::Clipboard);
}

QString AdBlockBlockableItemsWidget::elementTypeToI18n(AdBlockBlockableItemsWidget::TypeElement type)
{
    QString result;
    switch (type) {
    case AdBlockBlockableItemsWidget::Image:
        result = i18n("Image");
        break;
    case AdBlockBlockableItemsWidget::Script:
        result = i18n("Script");
        break;
    case AdBlockBlockableItemsWidget::StyleSheet:
        result = i18n("Stylesheet");
        break;
    case AdBlockBlockableItemsWidget::Font:
        result = i18n("Font");
        break;
    case AdBlockBlockableItemsWidget::Frame:
        result = i18n("Frame");
        break;
    case AdBlockBlockableItemsWidget::XmlRequest:
        result = i18n("XML Request");
        break;
    case AdBlockBlockableItemsWidget::Object:
        result = i18n("Object");
        break;
    case AdBlockBlockableItemsWidget::Media:
        result = i18n("Audio/Video");
        break;
    case AdBlockBlockableItemsWidget::Popup:
        result = i18n("Popup window");
        break;
    case AdBlockBlockableItemsWidget::None:
    default:
        result = i18n("Unknown");
    }
    return result;
}

QString AdBlockBlockableItemsWidget::elementType(AdBlockBlockableItemsWidget::TypeElement type)
{
    QString result;
    switch (type) {
    case AdBlockBlockableItemsWidget::Image:
        result = QStringLiteral("image");
        break;
    case AdBlockBlockableItemsWidget::Script:
        result = QStringLiteral("script");
        break;
    case AdBlockBlockableItemsWidget::StyleSheet:
        result = QStringLiteral("stylesheet");
        break;
    case AdBlockBlockableItemsWidget::Font:
        result = QStringLiteral("font");
        break;
    case AdBlockBlockableItemsWidget::Frame:
        result = QStringLiteral("frame");
        break;
    case AdBlockBlockableItemsWidget::XmlRequest:
        result = QStringLiteral("xmlhttprequest");
        break;
    case AdBlockBlockableItemsWidget::Object:
        result = QStringLiteral("other");
        break;
    case AdBlockBlockableItemsWidget::Media:
        result = QStringLiteral("media");
        break;
    case AdBlockBlockableItemsWidget::Popup:
        result = QStringLiteral("popup");
        break;
    case AdBlockBlockableItemsWidget::None:
    default:
        qCDebug(ADBLOCKINTERCEPTOR_LOG) << " unknown type " << type;
    }
    return result;
}

void AdBlockBlockableItemsWidget::slotRemoveFilter()
{
    //TODO
    qCDebug(ADBLOCKINTERCEPTOR_LOG) << " AdBlockBlockableItemsWidget::slotRemoveFilter not implement yet";
}
