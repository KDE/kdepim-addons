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

#include "rendertest.h"

#include "testobjecttreesource.h"

#include <MimeTreeParser/ObjectTreeParser>
#include <MessageViewer/CSSHelperBase>
#include <MimeTreeParser/FileHtmlWriter>

#include <KMime/Message>
#include <QTest>
#include <QDir>
#include <QIcon>
#include <QProcess>

#ifndef Q_OS_WIN
void initLocale()
{
    setenv("LC_ALL", "en_US.utf-8", 1);
}

Q_CONSTRUCTOR_FUNCTION(initLocale)
#endif

void RenderTest::testRender_data()
{
    QTest::addColumn<QString>("mailFileName");
    QTest::addColumn<QString>("referenceFileName");
    QTest::addColumn<QString>("outFileName");

    QDir dir(QStringLiteral(MAIL_DATA_DIR));
    const QStringList lst = dir.entryList(QStringList(QLatin1String("*.mbox")), QDir::Files | QDir::Readable | QDir::NoSymLinks);
    for (const QString &file : lst) {
        if (!QFile::exists(dir.path() + QLatin1Char('/') + file + QLatin1String(".html"))) {
            continue;
        }
        QTest::newRow(file.toLatin1()) << QString(dir.path() + QLatin1Char('/') +  file) << QString(dir.path() + QLatin1Char('/') + file + QLatin1String(".html"))
                                       << QString(file + QLatin1String(".out"));
    }
}

void RenderTest::testRender()
{
    QFETCH(QString, mailFileName);
    QFETCH(QString, referenceFileName);
    QFETCH(QString, outFileName);

    const QString htmlFileName = outFileName + QLatin1String(".html");

    QIcon::setThemeName(QStringLiteral("oxygen"));

    // load input mail
    QFile mailFile(mailFileName);
    QVERIFY(mailFile.open(QIODevice::ReadOnly));
    const QByteArray mailData = KMime::CRLFtoLF(mailFile.readAll());
    QVERIFY(!mailData.isEmpty());
    KMime::Message::Ptr msg(new KMime::Message);
    msg->setContent(mailData);
    msg->parse();

    // render the mail
    MimeTreeParser::FileHtmlWriter fileWriter(outFileName);
    QImage paintDevice;
    MessageViewer::CSSHelperBase cssHelper(&paintDevice);
    MimeTreeParser::NodeHelper nodeHelper;
    TestObjectTreeSource testSource(&fileWriter, &cssHelper);
    MimeTreeParser::ObjectTreeParser otp(&testSource, &nodeHelper);

    fileWriter.begin(QString());
    fileWriter.queue(QStringLiteral("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
                                    "<html>\n"
                                    "<body>\n"));

    otp.parseObjectTree(msg.data());

    fileWriter.queue(QStringLiteral("</body></html>"));
    fileWriter.flush();
    fileWriter.end();

    QVERIFY(QFile::exists(outFileName));

    // validate xml and pretty-print for comparisson
    // TODO add proper cmake check for xmllint and diff
    QStringList args = QStringList()
                       << QStringLiteral("--format")
                       << QStringLiteral("--encode")
                       << QStringLiteral("UTF8")
                       << QStringLiteral("--output")
                       << htmlFileName
                       << outFileName;
    QCOMPARE(QProcess::execute(QLatin1String("xmllint"), args), 0);

    // get rid of system dependent or random paths
    {
        QFile f(htmlFileName);
        QVERIFY(f.open(QIODevice::ReadOnly));
        QString content = QString::fromUtf8(f.readAll());
        f.close();
        content.replace(QRegExp(QLatin1String("\"file:[^\"]*[/(?:%2F)]([^\"/(?:%2F)]*)\"")), QStringLiteral("\"file:\\1\""));
        QVERIFY(f.open(QIODevice::WriteOnly | QIODevice::Truncate));
        f.write(content.toUtf8());
        f.close();
    }

    // compare to reference file
    args = QStringList()
           << QStringLiteral("-u")
           << referenceFileName
           << htmlFileName;
    QProcess proc;
    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(QStringLiteral("diff"), args);
    QVERIFY(proc.waitForFinished());

    QCOMPARE(proc.exitCode(), 0);
}

QTEST_MAIN(RenderTest)
