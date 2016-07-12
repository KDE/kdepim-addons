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

#include "automaticaddcontactswidgettest.h"
#include "../automaticaddcontactsconfigurewidget.h"

#include <QCheckBox>
#include <QTest>
#include <QVBoxLayout>
#include <QStandardPaths>
#include <QLabel>
#include <QStandardItemModel>
#include <AkonadiWidgets/CollectionComboBox>
#include <AkonadiCore/EntityTreeModel>
#include <KContacts/Addressee>

AutomaticAddContactsWidgetTest::AutomaticAddContactsWidgetTest(QObject *parent)
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

AutomaticAddContactsWidgetTest::~AutomaticAddContactsWidgetTest()
{

}

AutomaticAddContactsWidget *AutomaticAddContactsWidgetTest::createContactWidget()
{
    AutomaticAddContactsWidget *w = new AutomaticAddContactsWidget(0, mComboboxModel);
    return w;
}

void AutomaticAddContactsWidgetTest::shouldHaveDefaultValue()
{
    AutomaticAddContactsWidget *w = new AutomaticAddContactsWidget(createContactWidget());
    QVBoxLayout *vboxlayout = w->findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);

    QCheckBox *mEnabled = w->findChild<QCheckBox *>(QStringLiteral("enabled"));
    QVERIFY(mEnabled);
    QVERIFY(!mEnabled->text().isEmpty());
    QVERIFY(!mEnabled->isChecked());

    QHBoxLayout *hlay = w->findChild<QHBoxLayout *>(QStringLiteral("folderlayout"));
    QVERIFY(hlay);
    QCOMPARE(hlay->margin(), 0);

    QLabel *lab = w->findChild<QLabel *>(QStringLiteral("labelfolder"));
    QVERIFY(lab);
    QVERIFY(!lab->text().isEmpty());


    Akonadi::CollectionComboBox *mCollectionCombobox = w->findChild<Akonadi::CollectionComboBox *>(QStringLiteral("akonadicombobox"));
    QVERIFY(mCollectionCombobox);
    delete w;
}

void AutomaticAddContactsWidgetTest::shouldResetValue()
{
    AutomaticAddContactsWidget *w = new AutomaticAddContactsWidget(createContactWidget());
    QCheckBox *mEnabled = w->findChild<QCheckBox *>(QStringLiteral("enabled"));
    QVERIFY(!mEnabled->isChecked());
    mEnabled->setChecked(true);
    QVERIFY(mEnabled->isChecked());

    w->resetSettings();
    QVERIFY(!mEnabled->isChecked());
    delete w;
}

QTEST_MAIN(AutomaticAddContactsWidgetTest)
