/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "automaticaddcontactstabwidgettest.h"
#include "../automaticaddcontactstabwidget.h"
#include <QCheckBox>
#include <QTest>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QLabel>
#include <QStandardItemModel>
#include <AkonadiWidgets/CollectionComboBox>
#include <AkonadiCore/EntityTreeModel>
#include <KContacts/Addressee>

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

        QStandardItem *item = new QStandardItem(collection.name());
        item->setData(QVariant::fromValue(collection),
                      Akonadi::EntityTreeModel::CollectionRole);
        item->setData(QVariant::fromValue(collection.id()),
                      Akonadi::EntityTreeModel::CollectionIdRole);

        mComboboxModel->appendRow(item);
    }
}

AutomaticAddContactsTabWidgetTest::~AutomaticAddContactsTabWidgetTest()
{
}

AutomaticAddContactsTabWidget *AutomaticAddContactsTabWidgetTest::createContactWidget()
{
    AutomaticAddContactsTabWidget *w = new AutomaticAddContactsTabWidget(nullptr, mComboboxModel);
    return w;
}

void AutomaticAddContactsTabWidgetTest::shouldHaveDefaultValue()
{
    AutomaticAddContactsTabWidget *w = new AutomaticAddContactsTabWidget(createContactWidget());
    QVBoxLayout *vboxlayout = w->findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);

    QCheckBox *mEnabled = w->findChild<QCheckBox *>(QStringLiteral("enabled"));
    QVERIFY(mEnabled);
    QVERIFY(!mEnabled->text().isEmpty());
    QVERIFY(!mEnabled->isChecked());

    QHBoxLayout *hlay = w->findChild<QHBoxLayout *>(QStringLiteral("folderlayout"));
    QVERIFY(hlay);
    QCOMPARE(hlay->contentsMargins(), QMargins(0, 0, 0, 0));

    QLabel *lab = w->findChild<QLabel *>(QStringLiteral("labelfolder"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());

    Akonadi::CollectionComboBox *mCollectionCombobox = w->findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    QVERIFY(mCollectionCombobox);
    delete w;
}

void AutomaticAddContactsTabWidgetTest::shouldResetValue()
{
    AutomaticAddContactsTabWidget *w = new AutomaticAddContactsTabWidget(createContactWidget());
    QCheckBox *mEnabled = w->findChild<QCheckBox *>(QStringLiteral("enabled"));
    QVERIFY(!mEnabled->isChecked());
    mEnabled->setChecked(true);
    QVERIFY(mEnabled->isChecked());

    w->resetSettings();
    QVERIFY(!mEnabled->isChecked());
    delete w;
}

QTEST_MAIN(AutomaticAddContactsTabWidgetTest)
