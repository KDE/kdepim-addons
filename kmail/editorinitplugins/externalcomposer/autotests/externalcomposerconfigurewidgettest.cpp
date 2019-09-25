/*
   Copyright (C) 2017-2019 Montel Laurent <montel@kde.org>

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

#include "externalcomposerconfigurewidgettest.h"
#include "../externalcomposerconfigurewidget.h"
#include <QCheckBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTest>
#include <KUrlRequester>
#include <QStandardPaths>

ExternalComposerConfigureWidgetTest::ExternalComposerConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void ExternalComposerConfigureWidgetTest::shouldHaveDefaultValues()
{
    ExternalComposerConfigureWidget w(nullptr);
    QVBoxLayout *vboxlayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);
    QCOMPARE(vboxlayout->contentsMargins(), QMargins(0, 0, 0, 0));

    QCheckBox *mExternalEditorCheck = w.findChild<QCheckBox *>(QStringLiteral("enabled"));
    QVERIFY(mExternalEditorCheck);
    QVERIFY(!mExternalEditorCheck->text().isEmpty());
    QVERIFY(!mExternalEditorCheck->isChecked());

    QLabel *urlrequesterlabel = w.findChild<QLabel *>(QStringLiteral("urlrequesterlabel"));
    QVERIFY(urlrequesterlabel);
    QVERIFY(!urlrequesterlabel->text().isEmpty());

    QLabel *explanationlabel = w.findChild<QLabel *>(QStringLiteral("explanationlabel"));
    QVERIFY(explanationlabel);
    QVERIFY(!explanationlabel->text().isEmpty());
    QVERIFY(!explanationlabel->isEnabled());

    KUrlRequester *mEditorRequester = w.findChild<KUrlRequester *>(QStringLiteral("mEditorRequester"));
    QVERIFY(mEditorRequester);
    QVERIFY(!mEditorRequester->isEnabled());
}

void ExternalComposerConfigureWidgetTest::shouldEnableDisableElements()
{
    ExternalComposerConfigureWidget w(nullptr);

    QCheckBox *mExternalEditorCheck = w.findChild<QCheckBox *>(QStringLiteral("enabled"));
    QVERIFY(mExternalEditorCheck);
    QVERIFY(!mExternalEditorCheck->isChecked());

    KUrlRequester *mEditorRequester = w.findChild<KUrlRequester *>(QStringLiteral("mEditorRequester"));
    QVERIFY(mEditorRequester);
    QVERIFY(!mEditorRequester->isEnabled());

    QLabel *urlrequesterlabel = w.findChild<QLabel *>(QStringLiteral("urlrequesterlabel"));
    QVERIFY(urlrequesterlabel);
    QVERIFY(urlrequesterlabel->isEnabled());

    QLabel *explanationlabel = w.findChild<QLabel *>(QStringLiteral("explanationlabel"));
    QVERIFY(!explanationlabel->isEnabled());

    mExternalEditorCheck->toggle();
    QVERIFY(mExternalEditorCheck->isChecked());
    QVERIFY(mEditorRequester->isEnabled());
    QVERIFY(urlrequesterlabel->isEnabled());
    QVERIFY(explanationlabel->isEnabled());

    mExternalEditorCheck->toggle();
    QVERIFY(!mExternalEditorCheck->isChecked());
    QVERIFY(!mEditorRequester->isEnabled());
    QVERIFY(urlrequesterlabel->isEnabled());
    QVERIFY(!explanationlabel->isEnabled());
}

QTEST_MAIN(ExternalComposerConfigureWidgetTest)
