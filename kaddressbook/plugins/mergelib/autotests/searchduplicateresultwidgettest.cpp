/*
   SPDX-FileCopyrightText: 2014-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "searchduplicateresultwidgettest.h"
#include "../searchduplicate/searchduplicateresultwidget.h"
#include "../searchduplicate/resultduplicatetreewidget.h"
#include "../widgets/mergecontactloseinformationwarning.h"
#include <Akonadi/Contact/GrantleeContactViewer>
#include <QSplitter>
#include <QLayout>
#include <QLabel>
#include <QTest>
#include <QPushButton>
#include <QStandardItemModel>
#include <AkonadiWidgets/CollectionComboBox>
#include <AkonadiCore/EntityTreeModel>
#include <KContacts/Addressee>

using namespace KContacts;
namespace KABMergeContacts {
KADDRESSBOOKMERGELIB_EXPORT QAbstractItemModel *_k_searchDuplicateResultStubModel = nullptr;
}

SearchDuplicateResultWidgetTest::SearchDuplicateResultWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardItemModel *model = new QStandardItemModel;
    for (int id = 42; id < 51; ++id) {
        Akonadi::Collection collection(id);
        collection.setRights(Akonadi::Collection::AllRights);
        collection.setName(QString::number(id));
        collection.setContentMimeTypes(QStringList() << Addressee::mimeType());

        QStandardItem *item = new QStandardItem(collection.name());
        item->setData(QVariant::fromValue(collection),
                      Akonadi::EntityTreeModel::CollectionRole);
        item->setData(QVariant::fromValue(collection.id()),
                      Akonadi::EntityTreeModel::CollectionIdRole);

        model->appendRow(item);
    }
    KABMergeContacts::_k_searchDuplicateResultStubModel = model;
}

SearchDuplicateResultWidgetTest::~SearchDuplicateResultWidgetTest()
{
}

void SearchDuplicateResultWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::SearchDuplicateResultWidget w;
    QCOMPARE(w.layout()->contentsMargins(), QMargins(0, 0, 0, 0));

    KABMergeContacts::ResultDuplicateTreeWidget *tree = w.findChild<KABMergeContacts::ResultDuplicateTreeWidget *>(QStringLiteral("result_treewidget"));
    QVERIFY(tree);
    QCOMPARE(tree->topLevelItemCount(), 0);
    QSplitter *splitter = w.findChild<QSplitter *>(QStringLiteral("splitter"));
    QVERIFY(splitter);
    QVERIFY(!splitter->childrenCollapsible());
    KAddressBookGrantlee::GrantleeContactViewer *viewer = w.findChild<KAddressBookGrantlee::GrantleeContactViewer *>(QStringLiteral("contact_viewer"));
    QVERIFY(viewer);
    QLabel *lab = w.findChild<QLabel *>(QStringLiteral("select_addressbook_label"));
    lab->setObjectName(QStringLiteral("select_addressbook_label"));
    QPushButton *pushButton = w.findChild<QPushButton *>(QStringLiteral("merge_contact_button"));
    QVERIFY(pushButton);
    QVERIFY(!pushButton->isEnabled());

    KABMergeContacts::MergeContactLoseInformationWarning *warning = w.findChild<KABMergeContacts::MergeContactLoseInformationWarning *>(QStringLiteral("mergecontactwarning"));
    QVERIFY(warning);

    Akonadi::CollectionComboBox *combobox = w.findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    QVERIFY(combobox);
}

void SearchDuplicateResultWidgetTest::shouldHaveMergeButtonEnabled()
{
    KABMergeContacts::SearchDuplicateResultWidget w;
    KABMergeContacts::ResultDuplicateTreeWidget *tree = w.findChild<KABMergeContacts::ResultDuplicateTreeWidget *>(QStringLiteral("result_treewidget"));
    QVERIFY(tree);
    QCOMPARE(tree->topLevelItemCount(), 0);
    Akonadi::Item::List lst;
    lst << Akonadi::Item(42);
    lst << Akonadi::Item(43);
    lst << Akonadi::Item(44);
    //QVector<Akonadi::Item::List> itemLst;
#if 0 //FIXME
    tree->setContacts(itemLst);
    QVERIFY(tree->topLevelItemCount() > 0);

    QPushButton *pushButton = w.findChild<QPushButton *>(QStringLiteral("merge_contact_button"));
    QVERIFY(pushButton);
    QVERIFY(!pushButton->isEnabled());

    Akonadi::CollectionComboBox *combobox = w.findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    QVERIFY(combobox);
#endif
}

QTEST_MAIN(SearchDuplicateResultWidgetTest)
