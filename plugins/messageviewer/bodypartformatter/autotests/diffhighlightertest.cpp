/*
   SPDX-FileCopyrightText: 2017-2025 Laurent Montel <montel@kde.org>

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

DiffHighlighterTest::DiffHighlighterTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

QString readDiffFile(const QString &diffFile)
{
    QFile file(diffFile);
    file.open(QIODevice::ReadOnly);
    Q_ASSERT(file.isOpen());
    const QString data = QString::fromUtf8(file.readAll());
    return data;
}

void DiffHighlighterTest::shouldGenerateDiff_data()
{
    QTest::addColumn<QString>("input");
    QTest::newRow("test1") << QStringLiteral("test1");
    QTest::newRow("kcontact1") << QStringLiteral("kcontact1");
    QTest::newRow("diff-akonadiconsole-16.12-master") << QStringLiteral("diff-akonadiconsole-16.12-master");
}

void DiffHighlighterTest::shouldGenerateDiff()
{
    QFETCH(QString, input);

    const QString originalFile = QStringLiteral(DIFF_DATA_DIR) + QLatin1Char('/') + input + QStringLiteral(".diff");
    const QString refFile = QStringLiteral(DIFF_DATA_DIR) + QLatin1Char('/') + input + QStringLiteral("-ref.diff");
    const QString generatedFile = QStringLiteral(DIFF_DATA_DIR) + QLatin1Char('/') + input + QStringLiteral("-generated.diff");
    QString diff = readDiffFile(originalFile);

    // Create generated file
    QFile f(generatedFile);
    QVERIFY(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
    QTextStream s(&f);

    KSyntaxHighlighting::Repository repo;
    Highlighter highLighter(&s);
    highLighter.setDefinition(repo.definitionForName(QStringLiteral("Diff")));
    highLighter.setTheme(repo.defaultTheme(KSyntaxHighlighting::Repository::LightTheme));
    highLighter.highlight(diff);

    s.flush();
    f.close();

    // compare to reference file
    QStringList args = QStringList() << QStringLiteral("-u") << refFile << generatedFile;
    QProcess proc;
    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(QStringLiteral("diff"), args);
    QVERIFY(proc.waitForFinished());

    QCOMPARE(proc.exitCode(), 0);
}

QTEST_MAIN(DiffHighlighterTest)

#include "moc_diffhighlightertest.cpp"
