/*
   SPDX-FileCopyrightText: 2022-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openurlwithconfigurecreatewidgettest.h"
#include "openurlwithconfigurecreatewidget.h"
#include <KUrlRequester>
#include <QCheckBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_MAIN(OpenUrlWithConfigureCreateWidgetTest)
OpenUrlWithConfigureCreateWidgetTest::OpenUrlWithConfigureCreateWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OpenUrlWithConfigureCreateWidgetTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureCreateWidget w;

    const auto mainLayout = w.findChild<QFormLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    const auto mServerName = w.findChild<QLineEdit *>(u"mServerName"_s);
    QVERIFY(mServerName);
    QVERIFY(mServerName->text().isEmpty());
    QVERIFY(mServerName->isClearButtonEnabled());

    const auto mCommandLine = w.findChild<QLineEdit *>(u"mCommandLine"_s);
    QVERIFY(mCommandLine);
    QVERIFY(mCommandLine->text().isEmpty());
    QVERIFY(mCommandLine->isClearButtonEnabled());

    const auto formatHelp = w.findChild<QLabel *>(u"formatHelp"_s);
    QVERIFY(formatHelp);
    QCOMPARE(formatHelp->contextMenuPolicy(), Qt::NoContextMenu);

    const auto mExecutable = w.findChild<KUrlRequester *>(u"mEditorRequester"_s);
    QVERIFY(mExecutable);

    const auto mEnabled = w.findChild<QCheckBox *>(u"mEnabled"_s);
    QVERIFY(mEnabled);
}

#include "moc_openurlwithconfigurecreatewidgettest.cpp"
