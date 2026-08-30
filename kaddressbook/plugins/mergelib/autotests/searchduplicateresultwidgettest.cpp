/*
   SPDX-FileCopyrightText: 2014-2026 Laurent Montel <montel@kde.org>

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
using namespace Qt::Literals::StringLiterals;

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

    const auto tree = w.findChild<KABMergeContacts::ResultDuplicateTreeWidget *>(u"result_treewidget"_s);
    QVERIFY(tree);
    QCOMPARE(tree->topLevelItemCount(), 0);
    const auto splitter = w.findChild<QSplitter *>(u"splitter"_s);
    QVERIFY(splitter);
    QVERIFY(!splitter->childrenCollapsible());
    const auto viewer = w.findChild<KAddressBookGrantlee::GrantleeContactViewer *>(u"contact_viewer"_s);
    QVERIFY(viewer);
    const auto lab = w.findChild<QLabel *>(u"select_addressbook_label"_s);
    lab->setObjectName("select_addressbook_label"_L1);
    const auto pushButton = w.findChild<QPushButton *>(u"merge_contact_button"_s);
    QVERIFY(pushButton);
    QVERIFY(!pushButton->isEnabled());

    const auto warning = w.findChild<KABMergeContacts::MergeContactLoseInformationWarning *>(u"mergecontactwarning"_s);
    QVERIFY(warning);

    const auto combobox = w.findChild<Akonadi::CollectionComboBox *>(u"akonadicombobox"_s);
    QVERIFY(combobox);
}

void SearchDuplicateResultWidgetTest::shouldHaveMergeButtonEnabled()
{
    KABMergeContacts::SearchDuplicateResultWidget w;
    const auto tree = w.findChild<KABMergeContacts::ResultDuplicateTreeWidget *>(u"result_treewidget"_s);
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

    QPushButton *pushButton = w.findChild<QPushButton *>(u"merge_contact_button"_s);
    QVERIFY(pushButton);
    QVERIFY(!pushButton->isEnabled());

    Akonadi::CollectionComboBox *combobox = w.findChild<Akonadi::CollectionComboBox *>(u"akonadicombobox"_s);
    QVERIFY(combobox);
#endif
}

QTEST_MAIN(SearchDuplicateResultWidgetTest)

#include "moc_searchduplicateresultwidgettest.cpp"
