/*
  SPDX-FileCopyrightText: 2010 Volker Krause <vkrause@kde.org>
  SPDX-FileCopyrightText: 2016 Sandro Knauß <sknauss@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <QFile>
#include <QProcess>
#include <QRegularExpression>
#include <QTest>

static void compareFile(const QString &outFile, const QString &referenceFile)
{
    QVERIFY(QFile::exists(outFile));

    const QString htmlFile = outFile + QStringLiteral(".html");
    // remove tailing newlines and spaces and make htmlmore uniform (breaks pre tags)
    {
        QFile f(outFile);
        QVERIFY(f.open(QIODevice::ReadOnly));
        QString content = QString::fromUtf8(f.readAll());
        f.close();
        content.replace(QRegularExpression(QStringLiteral("[\t ]+")), QStringLiteral(" "));
        content.replace(QRegularExpression(QStringLiteral("[\t ]*\n+[\t ]*")), QStringLiteral("\n"));
        content.replace(QRegularExpression(QStringLiteral("([\n\t ])\\1+")), QStringLiteral("\\1"));
        content.replace(QRegularExpression(QStringLiteral(">\n+[\t ]*")), QStringLiteral(">"));
        content.replace(QRegularExpression(QStringLiteral("[\t ]*\n+[\t ]*<")), QStringLiteral("<"));
        content.replace(QLatin1StringView("&nbsp;"), QLatin1StringView("NBSP_ENTITY_PLACEHOLDER")); // xmlling chokes on &nbsp;
        QVERIFY(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
        f.write(content.toUtf8());
        f.close();
    }

    // validate xml and pretty-print for comparison
    // TODO add proper cmake check for xmllint and diff
    QStringList args = QStringList() << QStringLiteral("--format") << QStringLiteral("--encode") << QStringLiteral("UTF8") << QStringLiteral("--output")
                                     << htmlFile << outFile;
    QCOMPARE(QProcess::execute(QStringLiteral("xmllint"), args), 0);

    // get rid of system dependent or random paths
    {
        QFile f(htmlFile);
        QVERIFY(f.open(QIODevice::ReadOnly));
        QString content = QString::fromUtf8(f.readAll());
        f.close();
        content.replace(QRegularExpression(QStringLiteral("\"file:[^\"]*[/(?:%2F)]([^\"/(?:%2F)]*)\"")), QStringLiteral("\"file:\\1\""));
        content.replace(QLatin1StringView("NBSP_ENTITY_PLACEHOLDER"), QLatin1StringView("&nbsp;")); // undo above transformation for xmllint
        content.replace(QRegularExpression(QStringLiteral("/bodypart/\\d+/")), QStringLiteral("/bodypart/0/"));
        QVERIFY(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
        f.write(content.toUtf8());
        f.close();
    }

    // compare to reference file
    args = QStringList() << QStringLiteral("-u") << referenceFile << htmlFile;
    QProcess proc;
    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(QStringLiteral("diff"), args);
    QVERIFY(proc.waitForFinished());

    QCOMPARE(proc.exitCode(), 0);
}
