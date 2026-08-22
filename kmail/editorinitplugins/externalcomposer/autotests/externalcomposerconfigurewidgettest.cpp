/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "externalcomposerconfigurewidgettest.h"
using namespace Qt::Literals::StringLiterals;

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
    const auto vboxlayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(vboxlayout);
    QCOMPARE(vboxlayout->contentsMargins(), QMargins());

    const auto mExternalEditorCheck = w.findChild<QCheckBox *>(u"enabled"_s);
    QVERIFY(mExternalEditorCheck);
    QVERIFY(!mExternalEditorCheck->text().isEmpty());
    QVERIFY(!mExternalEditorCheck->isChecked());

    const auto urlrequesterlabel = w.findChild<QLabel *>(u"urlrequesterlabel"_s);
    QVERIFY(urlrequesterlabel);
    QVERIFY(!urlrequesterlabel->text().isEmpty());

    const auto explanationlabel = w.findChild<QLabel *>(u"explanationlabel"_s);
    QVERIFY(explanationlabel);
    QVERIFY(!explanationlabel->text().isEmpty());
    QVERIFY(!explanationlabel->isEnabled());

    const auto mEditorRequester = w.findChild<KUrlRequester *>(u"mEditorRequester"_s);
    QVERIFY(mEditorRequester);
    QVERIFY(!mEditorRequester->isEnabled());
}

void ExternalComposerConfigureWidgetTest::shouldEnableDisableElements()
{
    ExternalComposerConfigureWidget w(nullptr);

    const auto mExternalEditorCheck = w.findChild<QCheckBox *>(u"enabled"_s);
    QVERIFY(mExternalEditorCheck);
    QVERIFY(!mExternalEditorCheck->isChecked());

    const auto mEditorRequester = w.findChild<KUrlRequester *>(u"mEditorRequester"_s);
    QVERIFY(mEditorRequester);
    QVERIFY(!mEditorRequester->isEnabled());

    const auto urlrequesterlabel = w.findChild<QLabel *>(u"urlrequesterlabel"_s);
    QVERIFY(urlrequesterlabel);
    QVERIFY(urlrequesterlabel->isEnabled());

    const auto explanationlabel = w.findChild<QLabel *>(u"explanationlabel"_s);
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
