/*
  Copyright (c) 2010 Volker Krause <vkrause@kde.org>
  Copyright (c) 2016 Sandro Knauß <sknauss@kde.org>

  This library is free software; you can redistribute it and/or modify it
  under the terms of the GNU Library General Public License as published by
  the Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This library is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
  License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to the
  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/

#include <QFile>
#include <QProcess>
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
        content.replace(QRegExp(QStringLiteral("[\t ]+")), QStringLiteral(" "));
        content.replace(QRegExp(QStringLiteral("[\t ]*\n+[\t ]*")), QStringLiteral("\n"));
        content.replace(QRegExp(QStringLiteral("([\n\t ])\\1+")), QStringLiteral("\\1"));
        content.replace(QRegExp(QStringLiteral(">\n+[\t ]*")), QStringLiteral(">"));
        content.replace(QRegExp(QStringLiteral("[\t ]*\n+[\t ]*<")), QStringLiteral("<"));
        content.replace(QLatin1String("&nbsp;"), QLatin1String("NBSP_ENTITY_PLACEHOLDER")); // xmlling chokes on &nbsp;
        QVERIFY(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
        f.write(content.toUtf8());
        f.close();
    }

    // validate xml and pretty-print for comparisson
    // TODO add proper cmake check for xmllint and diff
    QStringList args = QStringList()
                       << QStringLiteral("--format")
                       << QStringLiteral("--encode")
                       << QStringLiteral("UTF8")
                       << QStringLiteral("--output")
                       << htmlFile
                       << outFile;
    QCOMPARE(QProcess::execute(QStringLiteral("xmllint"), args), 0);

    // get rid of system dependent or random paths
    {
        QFile f(htmlFile);
        QVERIFY(f.open(QIODevice::ReadOnly));
        QString content = QString::fromUtf8(f.readAll());
        f.close();
        content.replace(QRegExp(QStringLiteral(
                                    "\"file:[^\"]*[/(?:%2F)]([^\"/(?:%2F)]*)\"")),
                        QStringLiteral("\"file:\\1\""));
        content.replace(QLatin1String("NBSP_ENTITY_PLACEHOLDER"), QLatin1String("&nbsp;")); // undo above transformation for xmllint
        content.replace(QRegExp(QStringLiteral("/bodypart/\\d+/")), QStringLiteral("/bodypart/0/"));
        QVERIFY(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
        f.write(content.toUtf8());
        f.close();
    }

    // compare to reference file
    args = QStringList()
           << QStringLiteral("-u")
           << referenceFile
           << htmlFile;
    QProcess proc;
    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(QStringLiteral("diff"), args);
    QVERIFY(proc.waitForFinished());

    QCOMPARE(proc.exitCode(), 0);
}
