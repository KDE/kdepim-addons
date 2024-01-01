/*
   SPDX-FileCopyrightText: 2017-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerconfigurewidgettest.h"
#include "../externalcomposerconfigurewidget.h"
#include <KUrlRequester>
#include <QCheckBox>
#include <QLabel>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>

ExternalComposerConfigureWidgetTest::ExternalComposerConfigureWidgetTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void ExternalComposerConfigureWidgetTest::shouldHaveDefaultValues()
{
    ExternalComposerConfigureWidget w(nullptr);
    auto vboxlayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(vboxlayout);
    QCOMPARE(vboxlayout->contentsMargins(), QMargins());

    auto mExternalEditorCheck = w.findChild<QCheckBox *>(QStringLiteral("enabled"));
    QVERIFY(mExternalEditorCheck);
    QVERIFY(!mExternalEditorCheck->text().isEmpty());
    QVERIFY(!mExternalEditorCheck->isChecked());

    auto urlrequesterlabel = w.findChild<QLabel *>(QStringLiteral("urlrequesterlabel"));
    QVERIFY(urlrequesterlabel);
    QVERIFY(!urlrequesterlabel->text().isEmpty());

    auto explanationlabel = w.findChild<QLabel *>(QStringLiteral("explanationlabel"));
    QVERIFY(explanationlabel);
    QVERIFY(!explanationlabel->text().isEmpty());
    QVERIFY(!explanationlabel->isEnabled());

    auto mEditorRequester = w.findChild<KUrlRequester *>(QStringLiteral("mEditorRequester"));
    QVERIFY(mEditorRequester);
    QVERIFY(!mEditorRequester->isEnabled());
}

void ExternalComposerConfigureWidgetTest::shouldEnableDisableElements()
{
    ExternalComposerConfigureWidget w(nullptr);

    auto mExternalEditorCheck = w.findChild<QCheckBox *>(QStringLiteral("enabled"));
    QVERIFY(mExternalEditorCheck);
    QVERIFY(!mExternalEditorCheck->isChecked());

    auto mEditorRequester = w.findChild<KUrlRequester *>(QStringLiteral("mEditorRequester"));
    QVERIFY(mEditorRequester);
    QVERIFY(!mEditorRequester->isEnabled());

    auto urlrequesterlabel = w.findChild<QLabel *>(QStringLiteral("urlrequesterlabel"));
    QVERIFY(urlrequesterlabel);
    QVERIFY(urlrequesterlabel->isEnabled());

    auto explanationlabel = w.findChild<QLabel *>(QStringLiteral("explanationlabel"));
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

#include "moc_externalcomposerconfigurewidgettest.cpp"
