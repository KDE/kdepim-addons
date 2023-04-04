/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "adblockblockableitemswidget.h"
#include "adblockcreatefilterdialog.h"
#include "adblockinterceptor_debug.h"
#include "adblockmanager.h"
#include "adblockutil.h"
#include <KConfigGroup>
#include <KIO/JobUiDelegateFactory>
#include <KIO/OpenUrlJob>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KTreeWidgetSearchLine>
#include <PimCommon/CustomTreeView>
#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QMenu>
#include <QPointer>
#include <QVBoxLayout>
#include <WebEngineViewer/WebEngineScript>
#include <adblockblockableitemsjob.h>
using namespace AdBlock;

AdBlockBlockableItemsWidget::AdBlockBlockableItemsWidget(QWidget *parent)
    : QWidget(parent)
{
    auto lay = new QVBoxLayout(this);
    lay->setContentsMargins({});
    mCustomTreeView = new PimCommon::CustomTreeView(this);
    mCustomTreeView->setDefaultText(i18n("No blockable element found."));

    mCustomTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    mCustomTreeView->setAlternatingRowColors(true);
    mCustomTreeView->setRootIsDecorated(false);
    connect(mCustomTreeView, &PimCommon::CustomTreeView::customContextMenuRequested, this, &AdBlockBlockableItemsWidget::slotCustomContextMenuRequested);

    const QStringList lst = {i18n("Filter"), i18n("Address"), i18n("Type")};
    mCustomTreeView->setHeaderLabels(lst);

    auto searchLine = new KTreeWidgetSearchLine(this, mCustomTreeView);
    searchLine->setPlaceholderText(i18n("Search..."));

    lay->addWidget(searchLine);
    lay->addWidget(mCustomTreeView);

    readConfig();
}

AdBlockBlockableItemsWidget::~AdBlockBlockableItemsWidget()
{
    writeConfig();
}

void AdBlockBlockableItemsWidget::setAdblockResult(const QList<AdBlockResult> &result)
{
    for (const AdBlockResult &res : result) {
        auto item = new QTreeWidgetItem(mCustomTreeView);
        item->setText(Url, res.src);
        switch (res.type) {
        case AdBlock::AdBlockBlockableItemsJob::UnKnown:
            qCDebug(ADBLOCKINTERCEPTOR_LOG) << " unknown adblock type : " << res.src;
            // TODO ?
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
        item->setForeground(FilterValue, Qt::red);
    }
    mCustomTreeView->setShowDefaultText(mCustomTreeView->model()->rowCount() == 0);
    // TODO read existing list for enable/disable it.
}

void AdBlockBlockableItemsWidget::saveFilters()
{
    for (int i = 0; i < mCustomTreeView->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = mCustomTreeView->topLevelItem(i);
        const QString itemStr = item->text(FilterValue);
        if (!itemStr.isEmpty()) {
            AdblockManager::self()->addCustomRule(itemStr);
        }
    }
}

void AdBlockBlockableItemsWidget::slotCustomContextMenuRequested(const QPoint &)
{
    QTreeWidgetItem *item = mCustomTreeView->currentItem();
    if (!item) {
        return;
    }

    QMenu menu(this);
    menu.addAction(QIcon::fromTheme(QStringLiteral("edit-copy")), i18n("Copy URL"), this, &AdBlockBlockableItemsWidget::slotCopyItem);
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
    KConfigGroup groupHeader(KSharedConfig::openStateConfig(), "AdBlockHeaders");
    groupHeader.writeEntry("HeaderState", mCustomTreeView->header()->saveState());
    groupHeader.sync();
}

void AdBlockBlockableItemsWidget::readConfig()
{
    KConfigGroup config(KSharedConfig::openStateConfig(), "AdBlockHeaders");
    mCustomTreeView->header()->restoreState(config.readEntry("HeaderState", QByteArray()));
}

void AdBlockBlockableItemsWidget::slotCopyFilterItem()
{
    QTreeWidgetItem *item = mCustomTreeView->currentItem();
    if (!item) {
        return;
    }
    QClipboard *cb = QApplication::clipboard();
    cb->setText(item->text(FilterValue), QClipboard::Clipboard);
}

void AdBlockBlockableItemsWidget::slotOpenItem()
{
    QTreeWidgetItem *item = mCustomTreeView->currentItem();
    if (!item) {
        return;
    }
    const QUrl url(item->text(Url));
    auto job = new KIO::OpenUrlJob(url);
    job->setUiDelegate(KIO::createDefaultJobUiDelegate(KJobUiDelegate::AutoHandlingEnabled, this));
    job->setRunExecutables(false);
    job->start();
}

void AdBlockBlockableItemsWidget::slotBlockItem()
{
    QTreeWidgetItem *item = mCustomTreeView->currentItem();
    if (!item) {
        return;
    }
    QPointer<AdBlockCreateFilterDialog> dlg = new AdBlockCreateFilterDialog(this);
    dlg->setPattern(static_cast<TypeElement>(item->data(Type, Element).toInt()), item->text(Url));
    if (dlg->exec()) {
        const QString filter = dlg->filter();
        item->setText(FilterValue, filter);
        item->setToolTip(FilterValue, filter);
    }
    delete dlg;
}

void AdBlockBlockableItemsWidget::slotCopyItem()
{
    QTreeWidgetItem *item = mCustomTreeView->currentItem();
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
    QTreeWidgetItem *item = mCustomTreeView->currentItem();
    if (!item) {
        return;
    }

    item->setText(FilterValue, QString());
}
