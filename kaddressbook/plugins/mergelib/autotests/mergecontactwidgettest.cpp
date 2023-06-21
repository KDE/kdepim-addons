/*
   SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mergecontactwidgettest.h"
#include "../manualmerge/mergecontactwidget.h"
#include <Akonadi/EntityTreeModel>

#include <QListWidget>
#include <QPushButton>
#include <QSignalSpy>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTest>
#include <qtestmouse.h>

#include <widgets/mergecontactinfowidget.h>
#include <widgets/mergecontactloseinformationwarning.h>
using namespace KABMergeContacts;

namespace KABMergeContacts
{
extern KADDRESSBOOKMERGELIB_EXPORT QAbstractItemModel *_k_mergeStubModel;
}

MergeContactWidgetTest::MergeContactWidgetTest()
{
    qRegisterMetaType<Akonadi::Item::List>();
    qRegisterMetaType<Akonadi::Item>();
    qRegisterMetaType<Akonadi::Collection>();

    auto model = new QStandardItemModel;
    for (int id = 42; id < 51; ++id) {
        Akonadi::Collection collection(id);
        collection.setRights(Akonadi::Collection::AllRights);
        collection.setName(QString::number(id));
        collection.setContentMimeTypes(QStringList() << KContacts::Addressee::mimeType());

        auto item = new QStandardItem(collection.name());
        item->setData(QVariant::fromValue(collection), Akonadi::EntityTreeModel::CollectionRole);
        item->setData(QVariant::fromValue(collection.id()), Akonadi::EntityTreeModel::CollectionIdRole);

        model->appendRow(item);
    }
    KABMergeContacts::_k_mergeStubModel = model;
}

Akonadi::Item::List MergeContactWidgetTest::createItems()
{
    Akonadi::Item::List lst;
    lst.reserve(10);
    for (int i = 0; i < 10; ++i) {
        Akonadi::Item item(i);
        KContacts::Addressee address;
        item.setPayload(address);
        lst.append(item);
    }
    return lst;
}

void MergeContactWidgetTest::shouldHaveDefaultValueOnCreation()
{
    MergeContactWidget mergeWidget;
    auto listWidget = mergeWidget.findChild<QListWidget *>(QStringLiteral("listcontact"));
    QVERIFY(listWidget);
    QCOMPARE(listWidget->count(), 0);
    auto button = mergeWidget.findChild<QPushButton *>(QStringLiteral("mergebutton"));
    QVERIFY(button);
    QCOMPARE(button->isEnabled(), false);
    auto warningWidget = mergeWidget.findChild<MergeContactLoseInformationWarning *>(QStringLiteral("mergecontactwarning"));
    QVERIFY(warningWidget);
    QVERIFY(warningWidget->isHidden());

    auto splitter = mergeWidget.findChild<QSplitter *>(QStringLiteral("splitter"));
    QVERIFY(splitter);
    QVERIFY(!splitter->childrenCollapsible());
    for (int i = 0; i < splitter->count(); ++i) {
        const QString objName = splitter->widget(i)->objectName();

        const bool hasName = (objName == QLatin1String("selectcontactwidget")) || (objName == QLatin1String("mergecontactinfowidget"));
        QVERIFY(hasName);
    }
}

void MergeContactWidgetTest::shouldFillList()
{
    MergeContactWidget mergeWidget;
    mergeWidget.setContacts(createItems());
    auto listWidget = mergeWidget.findChild<QListWidget *>(QStringLiteral("listcontact"));
    QCOMPARE(listWidget->count(), 10);
    QCOMPARE(listWidget->selectedItems().count(), 0);
    auto button = mergeWidget.findChild<QPushButton *>(QStringLiteral("mergebutton"));
    QCOMPARE(button->isEnabled(), false);
}

void MergeContactWidgetTest::shouldFillListWithValidItem()
{
    Akonadi::Item::List lst = createItems();
    QCOMPARE(lst.count(), 10);
    lst.append(Akonadi::Item(25));
    MergeContactWidget mergeWidget;
    mergeWidget.setContacts(lst);
    auto listWidget = mergeWidget.findChild<QListWidget *>(QStringLiteral("listcontact"));
    QCOMPARE(listWidget->count(), 10);
}

void MergeContactWidgetTest::shouldEnableButton()
{
    MergeContactWidget mergeWidget;
    mergeWidget.setContacts(createItems());
    auto listWidget = mergeWidget.findChild<QListWidget *>(QStringLiteral("listcontact"));
    auto button = mergeWidget.findChild<QPushButton *>(QStringLiteral("mergebutton"));
    mergeWidget.show();
    QVERIFY(QTest::qWaitForWindowExposed(&mergeWidget));
    listWidget->item(0)->setCheckState(Qt::Checked);
    listWidget->item(1)->setCheckState(Qt::Checked);
    QCOMPARE(button->isEnabled(), true);
}

void MergeContactWidgetTest::shouldEmitSignalsWhenThereIsElementSelected()
{
#if 0 // FIXME
    MergeContactWidget mergeWidget;
    mergeWidget.setContacts(createItems());
    QListWidget *listWidget = mergeWidget.findChild<QListWidget *>(QStringLiteral("listcontact"));
    QPushButton *button = mergeWidget.findChild<QPushButton *>(QStringLiteral("mergebutton"));
    mergeWidget.show();
    QVERIFY(QTest::qWaitForWindowExposed(&mergeWidget));
    listWidget->item(0)->setCheckState(Qt::Checked);
    listWidget->item(1)->setCheckState(Qt::Checked);
    QSignalSpy spy(&mergeWidget, SIGNAL(mergeContact(Akonadi::Item::List,Akonadi::Collection)));
    QTest::mouseClick(button, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
    listWidget->item(1)->setCheckState(Qt::Unchecked);
    QTest::mouseClick(button, Qt::LeftButton);
    QCOMPARE(spy.count(), 1); //No new signal emitted when we are not 2 items checked
#endif
}

void MergeContactWidgetTest::shouldEmitSignalsWhenThereIsTwoElementsSelected()
{
#if 0 // FIXME
    MergeContactWidget mergeWidget;
    mergeWidget.setContacts(createItems());
    QListWidget *listWidget = mergeWidget.findChild<QListWidget *>(QStringLiteral("listcontact"));
    QPushButton *button = mergeWidget.findChild<QPushButton *>(QStringLiteral("mergebutton"));
    mergeWidget.show();
    QVERIFY(QTest::qWaitForWindowExposed(&mergeWidget));
    listWidget->item(0)->setCheckState(Qt::Checked);
    QSignalSpy spy(&mergeWidget, SIGNAL(mergeContact(Akonadi::Item::List,Akonadi::Collection)));
    QTest::mouseClick(button, Qt::LeftButton);
    QCOMPARE(spy.count(), 0);
    listWidget->item(1)->setCheckState(Qt::Checked);
    QTest::mouseClick(button, Qt::LeftButton);
    QCOMPARE(spy.count(), 1);
#endif
}

void MergeContactWidgetTest::shouldEmitSignalsWhenSelectContact()
{
#if 0 // FIXME
    MergeContactWidget mergeWidget;
    mergeWidget.setContacts(createItems());
    QListWidget *listWidget = mergeWidget.findChild<QListWidget *>(QStringLiteral("listcontact"));
    mergeWidget.show();
    QSignalSpy spy(&mergeWidget, SIGNAL(contactSelected(Akonadi::Item)));
    listWidget->item(1)->setSelected(true);
    QCOMPARE(spy.count(), 1);

    listWidget->clearSelection();
    QCOMPARE(spy.count(), 2);
#endif
}

QTEST_MAIN(MergeContactWidgetTest)

#include "moc_mergecontactwidgettest.cpp"
