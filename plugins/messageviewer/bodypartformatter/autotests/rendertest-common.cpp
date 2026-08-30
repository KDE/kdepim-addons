/*
  SPDX-FileCopyrightText: 2010 Volker Krause <vkrause@kde.org>
  SPDX-FileCopyrightText: 2016 Sandro Knauß <sknauss@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <QFile>
#include <QProcess>
#include <QRegularExpression>
#include <QTest>
using namespace Qt::Literals::StringLiterals;

using namespace Qt::Literals;

static void compareFile(const QString &outFile, const QString &referenceFile)
{
    QVERIFY(QFile::exists(outFile));

    const QString htmlFile = outFile + u".html"_s;
    // remove tailing newlines and spaces and make htmlmore uniform (breaks pre tags)
    {
        QFile f(outFile);
        QVERIFY(f.open(QIODevice::ReadOnly));
        QString content = QString::fromUtf8(f.readAll());
        f.close();
        content.replace(QRegularExpression(u"[\t ]+"_s), u" "_s);
        content.replace(QRegularExpression(u"[\t ]*\n+[\t ]*"_s), u"\n"_s);
        content.replace(QRegularExpression(u"([\n\t ])\\1+"_s), u"\\1"_s);
        content.replace(QRegularExpression(u">\n+[\t ]*"_s), u">"_s);
        content.replace(QRegularExpression(u"[\t ]*\n+[\t ]*<"_s), u"<"_s);
        content.replace(QLatin1StringView("&nbsp;"), QLatin1StringView("NBSP_ENTITY_PLACEHOLDER")); // xmlling chokes on &nbsp;
        QVERIFY(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
        f.write(content.toUtf8());
        f.close();
    }

    // validate xml and pretty-print for comparison
    // TODO add proper cmake check for xmllint and diff
    QStringList args = QStringList() << u"--format"_s << u"--encode"_s << u"UTF8"_s << u"--output"_s << htmlFile << outFile;
    QCOMPARE(QProcess::execute(u"xmllint"_s, args), 0);

    // get rid of system dependent or random paths
    {
        QFile f(htmlFile);
        QVERIFY(f.open(QIODevice::ReadOnly));
        QString content = QString::fromUtf8(f.readAll());
        f.close();
        content.replace(QRegularExpression(u"\"file:[^\"]*[/(?:%2F)]([^\"/(?:%2F)]*)\""_s), u"\"file:\\1\""_s);
        content.replace(QRegularExpression(u"src=\"/[^\"]*/([^\"/(?:%2F)]*)\""_s), u"src=\"file:\\1\""_s);
        content.replace(QLatin1StringView("NBSP_ENTITY_PLACEHOLDER"), QLatin1StringView("&nbsp;")); // undo above transformation for xmllint
        content.replace(QRegularExpression(u"/bodypart/\\d+/"_s), u"/bodypart/0/"_s);
        QVERIFY(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
        f.write(content.toUtf8());
        f.close();
    }

    // compare to reference file
    args = QStringList() << u"-u"_s << referenceFile << htmlFile;
    QProcess proc;
    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(u"diff"_s, args);
    QVERIFY(proc.waitForFinished());

    QCOMPARE(proc.exitCode(), 0);
}
