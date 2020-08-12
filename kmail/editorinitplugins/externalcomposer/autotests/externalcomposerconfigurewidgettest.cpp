/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
