/*
   SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "searchduplicateresultwidgettest.h"
#include "../searchduplicate/resultduplicatetreewidget.h"
#include "../searchduplicate/searchduplicateresultwidget.h"
#include "../widgets/mergecontactloseinformationwarning.h"
#include <Akonadi/CollectionComboBox>
#include <Akonadi/EntityTreeModel>
#include <Akonadi/GrantleeContactViewer>
#include <KContacts/Addressee>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTest>

using namespace KContacts;
namespace KABMergeContacts
{
QAbstractItemModel *_k_searchDuplicateResultStubModel = nullptr;
}

SearchDuplicateResultWidgetTest::SearchDuplicateResultWidgetTest(QObject *parent)
    : QObject(parent)
{
    auto model = new QStandardItemModel;
    for (int id = 42; id < 51; ++id) {
        Akonadi::Collection collection(id);
        collection.setRights(Akonadi::Collection::AllRights);
        collection.setName(QString::number(id));
        collection.setContentMimeTypes(QStringList() << Addressee::mimeType());

        auto item = new QStandardItem(collection.name());
        item->setData(QVariant::fromValue(collection), Akonadi::EntityTreeModel::CollectionRole);
        item->setData(QVariant::fromValue(collection.id()), Akonadi::EntityTreeModel::CollectionIdRole);

        model->appendRow(item);
    }
    KABMergeContacts::_k_searchDuplicateResultStubModel = model;
}

SearchDuplicateResultWidgetTest::~SearchDuplicateResultWidgetTest() = default;

void SearchDuplicateResultWidgetTest::shouldHaveDefaultValue()
{
    KABMergeContacts::SearchDuplicateResultWidget w;
    QCOMPARE(w.layout()->contentsMargins(), QMargins());

    auto tree = w.findChild<KABMergeContacts::ResultDuplicateTreeWidget *>(QStringLiteral("result_treewidget"));
    QVERIFY(tree);
    QCOMPARE(tree->topLevelItemCount(), 0);
    auto splitter = w.findChild<QSplitter *>(QStringLiteral("splitter"));
    QVERIFY(splitter);
    QVERIFY(!splitter->childrenCollapsible());
    auto viewer = w.findChild<KAddressBookGrantlee::GrantleeContactViewer *>(QStringLiteral("contact_viewer"));
    QVERIFY(viewer);
    auto lab = w.findChild<QLabel *>(QStringLiteral("select_addressbook_label"));
    lab->setObjectName(QLatin1StringView("select_addressbook_label"));
    auto pushButton = w.findChild<QPushButton *>(QStringLiteral("merge_contact_button"));
    QVERIFY(pushButton);
    QVERIFY(!pushButton->isEnabled());

    auto warning = w.findChild<KABMergeContacts::MergeContactLoseInformationWarning *>(QStringLiteral("mergecontactwarning"));
    QVERIFY(warning);

    auto combobox = w.findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    QVERIFY(combobox);
}

void SearchDuplicateResultWidgetTest::shouldHaveMergeButtonEnabled()
{
    KABMergeContacts::SearchDuplicateResultWidget w;
    auto tree = w.findChild<KABMergeContacts::ResultDuplicateTreeWidget *>(QStringLiteral("result_treewidget"));
    QVERIFY(tree);
    QCOMPARE(tree->topLevelItemCount(), 0);
    Akonadi::Item::List lst;
    lst << Akonadi::Item(42);
    lst << Akonadi::Item(43);
    lst << Akonadi::Item(44);
    // QList<Akonadi::Item::List> itemLst;
#if 0 // FIXME
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

#include "moc_searchduplicateresultwidgettest.cpp"
