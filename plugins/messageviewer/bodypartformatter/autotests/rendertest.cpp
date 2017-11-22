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
#include <QStandardPaths>

#ifndef Q_OS_WIN
void initLocale()
{
    setenv("KDEHOME", QFile::encodeName(QDir::homePath() + QString::fromLatin1(
                                            "/.qttest")).constData(), 1);
    setenv("LC_ALL", "en_US.utf-8", 1);
    setenv("TZ", "UTC", 1);
    QStandardPaths::setTestModeEnabled(true);
    QIcon::setThemeName(QStringLiteral("breeze"));
    QLocale::setDefault(QLocale(QStringLiteral("en_US")));
}

Q_CONSTRUCTOR_FUNCTION(initLocale)
#endif

void RenderTest::testRender_data()
{
    QTest::addColumn<QString>("mailFileName");
    QTest::addColumn<QString>("referenceFileName");
    QTest::addColumn<QString>("outFileName");

    QDir dir(QStringLiteral(MAIL_DATA_DIR));
    const QStringList lst = dir.entryList(QStringList(QStringLiteral("*.mbox")), QDir::Files | QDir::Readable | QDir::NoSymLinks);
    for (const QString &file : lst) {
        if (!QFile::exists(dir.path() + QLatin1Char('/') + file + QStringLiteral(".html"))) {
            continue;
        }
        QTest::newRow(file.toLatin1()) << QString(dir.path() + QLatin1Char('/') +  file) << QString(dir.path() + QLatin1Char('/') + file + QStringLiteral(".html"))
                                       << QString(file + QStringLiteral(".out"));
    }
}

void RenderTest::testRender()
{
    QFETCH(QString, mailFileName);
    QFETCH(QString, referenceFileName);
    QFETCH(QString, outFileName);

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
    fileWriter.begin();
    QImage paintDevice;
    MessageViewer::CSSHelperBase cssHelper(&paintDevice);
    MimeTreeParser::NodeHelper nodeHelper;
    TestObjectTreeSource testSource(&fileWriter, &cssHelper);
    MimeTreeParser::ObjectTreeParser otp(&testSource, &nodeHelper);

    fileWriter.write(QStringLiteral("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
                                    "<html>\n"
                                    "<body>\n"));

    otp.parseObjectTree(msg.data());

    fileWriter.write(QStringLiteral("</body></html>"));
    fileWriter.end();

    compareFile(outFileName, referenceFileName);
}

void RenderTest::testRenderKeyDetails_data()
{
    QTest::addColumn<QString>("basename");
    QTest::newRow("message-with-openpgp-key.mbox") << QStringLiteral("message-with-openpgp-key.mbox");
    QTest::newRow("message-with-two-openpgp-key.mbox") << QStringLiteral("message-with-two-openpgp-key.mbox");
}

void RenderTest::testRenderKeyDetails()
{
    QFETCH(QString, basename);
    QString mailFileName = QStringLiteral(MAIL_DATA_DIR) + QLatin1Char('/') + basename;
    QString referenceFileName = QStringLiteral(MAIL_DATA_DIR) + QLatin1Char('/') + basename + QStringLiteral(".html");
    QString outFileName = basename + QStringLiteral(".out");

    // load input mail
    QFile mailFile(mailFileName);
    QVERIFY(mailFile.open(QIODevice::ReadOnly));
    const QByteArray mailData = KMime::CRLFtoLF(mailFile.readAll());
    QVERIFY(!mailData.isEmpty());
    KMime::Message::Ptr msg(new KMime::Message);
    msg->setContent(mailData);
    msg->parse();

    // render the mail
    QEventLoop loop;
    MimeTreeParser::FileHtmlWriter fileWriter(outFileName);
    fileWriter.begin();
    QImage paintDevice;
    MessageViewer::CSSHelperBase cssHelper(&paintDevice);
    MimeTreeParser::NodeHelper nodeHelper;
    TestObjectTreeSource testSource(&fileWriter, &cssHelper);
    testSource.setShowSignatureDetails(true);
    MimeTreeParser::ObjectTreeParser otp(&testSource, &nodeHelper);

    fileWriter.write(QStringLiteral("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
                                    "<html>\n"
                                    "<body>\n"));

    connect(&nodeHelper, &MimeTreeParser::NodeHelper::update, &loop, &QEventLoop::quit);
    otp.parseObjectTree(msg.data());

    fileWriter.write(QStringLiteral("</body></html>"));
    fileWriter.end();

    compareFile(outFileName, referenceFileName + QStringLiteral(".running"));
    loop.exec();

    {
        MimeTreeParser::ObjectTreeParser otp(&testSource, &nodeHelper);
        fileWriter.begin();
        fileWriter.write(QStringLiteral("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
                                    "<html>\n"
                                    "<body>\n"));
        otp.parseObjectTree(msg.data());

        fileWriter.write(QStringLiteral("</body></html>"));
        fileWriter.end();

        compareFile(outFileName, referenceFileName + QStringLiteral(".details"));
    }
}



void RenderTest::compareFile(const QString &outFile, const QString &referenceFile)
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

QTEST_MAIN(RenderTest)
