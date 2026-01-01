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
QTEST_MAIN(OpenUrlWithConfigureCreateWidgetTest)
OpenUrlWithConfigureCreateWidgetTest::OpenUrlWithConfigureCreateWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void OpenUrlWithConfigureCreateWidgetTest::shouldHaveDefaultValues()
{
    OpenUrlWithConfigureCreateWidget w;

    auto mainLayout = w.findChild<QFormLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mServerName = w.findChild<QLineEdit *>(QStringLiteral("mServerName"));
    QVERIFY(mServerName);
    QVERIFY(mServerName->text().isEmpty());
    QVERIFY(mServerName->isClearButtonEnabled());

    auto mCommandLine = w.findChild<QLineEdit *>(QStringLiteral("mCommandLine"));
    QVERIFY(mCommandLine);
    QVERIFY(mCommandLine->text().isEmpty());
    QVERIFY(mCommandLine->isClearButtonEnabled());

    auto formatHelp = w.findChild<QLabel *>(QStringLiteral("formatHelp"));
    QVERIFY(formatHelp);
    QCOMPARE(formatHelp->contextMenuPolicy(), Qt::NoContextMenu);

    auto mExecutable = w.findChild<KUrlRequester *>(QStringLiteral("mEditorRequester"));
    QVERIFY(mExecutable);

    auto mEnabled = w.findChild<QCheckBox *>(QStringLiteral("mEnabled"));
    QVERIFY(mEnabled);
}

#include "moc_openurlwithconfigurecreatewidgettest.cpp"
