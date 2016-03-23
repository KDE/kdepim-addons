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
#include "adblockinterceptor_debug.h"
#include <MessageViewer/WebEngineScript>

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

#include <KIOWidgets/KRun>
using namespace AdBlock;
template<typename Arg, typename R, typename C>
struct InvokeWrapper {
    R *receiver;
    void (C::*memberFunction)(Arg);
    void operator()(Arg result)
    {
        (receiver->*memberFunction)(result);
    }
};

template<typename Arg, typename R, typename C>

InvokeWrapper<Arg, R, C> invoke(R *receiver, void (C::*memberFunction)(Arg))
{
    InvokeWrapper<Arg, R, C> wrapper = {receiver, memberFunction};
    return wrapper;
}

AdBlockBlockableItemsWidget::AdBlockBlockableItemsWidget(QWidget *parent)
    : QWidget(parent),
      mWebEngineView(Q_NULLPTR)
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

void AdBlockBlockableItemsWidget::customContextMenuRequested(const QPoint &)
{
    QTreeWidgetItem *item = mListItems->currentItem();
    if (!item) {
        return;
    }

    QMenu menu;
    menu.addAction(i18n("Copy url"), this, SLOT(slotCopyItem()));
    if (!item->text(FilterValue).isEmpty()) {
        menu.addAction(i18n("Copy filter"), this, SLOT(slotCopyFilterItem()));
    }
    menu.addAction(i18n("Block item..."), this, SLOT(slotBlockItem()));
    menu.addSeparator();
    menu.addAction(i18n("Open"), this, SLOT(slotOpenItem()));
    if (!item->text(FilterValue).isEmpty()) {
        menu.addSeparator();
        menu.addAction(i18n("Remove filter"), this, SLOT(slotRemoveFilter()));
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

void AdBlockBlockableItemsWidget::setWebEngineView(QWebEngineView *view)
{
    mWebEngineView = view;
    searchBlockableItems();
}

void AdBlockBlockableItemsWidget::adaptSrc(QString &src, const QString &hostName)
{
    if (src.startsWith(QStringLiteral("http://")) || src.startsWith(QStringLiteral("https://"))) {
        //Nothing
    } else if (src.startsWith(QStringLiteral("//"))) {
        src = QLatin1String("https:") + src;
    } else if (src.startsWith(QLatin1Char('/'))) {
        src = QLatin1String("https://") + hostName + src;
    } else {
        src = QString();
    }
}


void AdBlockBlockableItemsWidget::handleSearchBlockableImageItems(const QVariant &result)
{
    //qDebug() << " AdBlockBlockableItemsWidget::handleSearchBlockableImageItems " << result;
    const QList<QVariant> lst = result.toList();
    const QUrl url = mWebEngineView->url();
    const QString host = url.host();
    Q_FOREACH (const QVariant &var, lst) {
        QMap<QString, QVariant> mapVariant = var.toMap();
        QString src = mapVariant.value(QStringLiteral("src")).toString();
        if (!src.isEmpty()) {
            adaptSrc(src, host);
            if (src.isEmpty()) {
                continue;
            }
            QTreeWidgetItem *item = new QTreeWidgetItem(mListItems);
            item->setText(Url, src);
            item->setText(Type, elementTypeToI18n(AdBlockBlockableItemsWidget::Image));
            item->setTextColor(FilterValue, Qt::red);
            item->setData(Type, Element, Image);
        }
    }
    mListItems->setShowDefaultText(mListItems->model()->rowCount() == 0);
    mWebEngineView->page()->runJavaScript(MessageViewer::WebEngineScript::findAllScripts(), invoke(this, &AdBlockBlockableItemsWidget::handleSearchBlockableScriptsItems));
}

void AdBlockBlockableItemsWidget::handleSearchBlockableScriptsItems(const QVariant &result)
{
    const QList<QVariant> lst = result.toList();
    const QUrl url = mWebEngineView->url();
    const QString host = url.host();
    Q_FOREACH (const QVariant &var, lst) {
        QMap<QString, QVariant> mapVariant = var.toMap();
        QString src = mapVariant.value(QStringLiteral("src")).toString();
        if (!src.isEmpty()) {
            adaptSrc(src, host);
            if (src.isEmpty()) {
                continue;
            }
            QTreeWidgetItem *item = new QTreeWidgetItem(mListItems);
            item->setText(Url, src);
            item->setText(Type, elementTypeToI18n(AdBlockBlockableItemsWidget::Script));
            item->setTextColor(FilterValue, Qt::red);
            item->setData(Type, Element, Script);
        }
    }
    mListItems->setShowDefaultText(mListItems->model()->rowCount() == 0);
    //TODO more check ?
}

void AdBlockBlockableItemsWidget::searchBlockableItems()
{
    if (mWebEngineView) {
        mListItems->clear();
        mWebEngineView->page()->runJavaScript(MessageViewer::WebEngineScript::findAllImages(), invoke(this, &AdBlockBlockableItemsWidget::handleSearchBlockableImageItems));
    }
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
#if 0
    QPointer<AdBlockCreateFilterDialog> dlg = new AdBlockCreateFilterDialog(this);
    dlg->setPattern(static_cast<TypeElement>(item->data(Type, Element).toInt()), item->text(Url));
    if (dlg->exec()) {
        const QString filter = dlg->filter();
        item->setText(FilterValue, filter);
    }
    delete dlg;
#endif
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
