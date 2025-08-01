/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactstabwidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "../automaticaddcontactstabwidget.h"
#include <Akonadi/CollectionComboBox>
#include <Akonadi/EntityTreeModel>
#include <KContacts/Addressee>
#include <QCheckBox>
#include <QLabel>
#include <QStandardItemModel>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

AutomaticAddContactsTabWidgetTest::AutomaticAddContactsTabWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
    mComboboxModel = new QStandardItemModel;
    for (int id = 42; id < 51; ++id) {
        Akonadi::Collection collection(id);
        collection.setRights(Akonadi::Collection::AllRights);
        collection.setName(QString::number(id));
        collection.setContentMimeTypes(QStringList() << KContacts::Addressee::mimeType());

        auto item = new QStandardItem(collection.name());
        item->setData(QVariant::fromValue(collection), Akonadi::EntityTreeModel::CollectionRole);
        item->setData(QVariant::fromValue(collection.id()), Akonadi::EntityTreeModel::CollectionIdRole);

        mComboboxModel->appendRow(item);
    }
}

AutomaticAddContactsTabWidgetTest::~AutomaticAddContactsTabWidgetTest() = default;

AutomaticAddContactsTabWidget *AutomaticAddContactsTabWidgetTest::createContactWidget()
{
    auto w = new AutomaticAddContactsTabWidget(nullptr, mComboboxModel);
    return w;
}

void AutomaticAddContactsTabWidgetTest::shouldHaveDefaultValue()
{
    auto w = new AutomaticAddContactsTabWidget(createContactWidget());
    auto vboxlayout = w->findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(vboxlayout);

    auto mEnabled = w->findChild<QCheckBox *>(u"enabled"_s);
    QVERIFY(mEnabled);
    QVERIFY(!mEnabled->text().isEmpty());
    QVERIFY(!mEnabled->isChecked());

    auto hlay = w->findChild<QHBoxLayout *>(u"folderlayout"_s);
    QVERIFY(hlay);
    QCOMPARE(hlay->contentsMargins(), QMargins());

    auto lab = w->findChild<QLabel *>(u"labelfolder"_s);
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    auto mCollectionCombobox = w->findChild<Akonadi::CollectionComboBox *>(u"akonadicombobox"_s);
    QVERIFY(mCollectionCombobox);
    delete w;
}

void AutomaticAddContactsTabWidgetTest::shouldResetValue()
{
    auto w = new AutomaticAddContactsTabWidget(createContactWidget());
    auto mEnabled = w->findChild<QCheckBox *>(u"enabled"_s);
    QVERIFY(!mEnabled->isChecked());
    mEnabled->setChecked(true);
    QVERIFY(mEnabled->isChecked());

    w->resetSettings();
    QVERIFY(!mEnabled->isChecked());
    delete w;
}

QTEST_MAIN(AutomaticAddContactsTabWidgetTest)

#include "moc_automaticaddcontactstabwidgettest.cpp"
