/*
   SPDX-FileCopyrightText: 2017-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "diffhighlightertest.h"
#include "../highlighter/highlighter.h"

#include <KSyntaxHighlighting/Definition>
#include <KSyntaxHighlighting/Repository>
#include <KSyntaxHighlighting/Theme>

#include <QProcess>
#include <QStandardPaths>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

DiffHighlighterTest::DiffHighlighterTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

QString readDiffFile(const QString &diffFile)
{
    QFile file(diffFile);
    if (!file.open(QIODevice::ReadOnly)) {
        return {};
    }
    Q_ASSERT(file.isOpen());
    const QString data = QString::fromUtf8(file.readAll());
    return data;
}

void DiffHighlighterTest::shouldGenerateDiff_data()
{
    QTest::addColumn<QString>("input");
    QTest::newRow("test1") << u"test1"_s;
    QTest::newRow("kcontact1") << u"kcontact1"_s;
    QTest::newRow("diff-akonadiconsole-16.12-master") << u"diff-akonadiconsole-16.12-master"_s;
}

void DiffHighlighterTest::shouldGenerateDiff()
{
    QFETCH(QString, input);

    const QString originalFile = QStringLiteral(DIFF_DATA_DIR) + QLatin1Char('/') + input + u".diff"_s;
    const QString refFile = QStringLiteral(DIFF_DATA_DIR) + QLatin1Char('/') + input + u"-ref.diff"_s;
    const QString generatedFile = QStringLiteral(DIFF_DATA_DIR) + QLatin1Char('/') + input + u"-generated.diff"_s;
    QString diff = readDiffFile(originalFile);

    // Create generated file
    QFile f(generatedFile);
    QVERIFY(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
    QTextStream s(&f);

    KSyntaxHighlighting::Repository repo;
    Highlighter highLighter(&s);
    highLighter.setDefinition(repo.definitionForName(u"Diff"_s));
    highLighter.setTheme(repo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
    highLighter.highlight(diff);

    s.flush();
    f.close();

    // compare to reference file
    QStringList args = QStringList() << u"-u"_s << refFile << generatedFile;
    QProcess proc;
    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(u"diff"_s, args);
    QVERIFY(proc.waitForFinished());

    QCOMPARE(proc.exitCode(), 0);
}

QTEST_MAIN(DiffHighlighterTest)

#include "moc_diffhighlightertest.cpp"
