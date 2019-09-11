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
#include "rendertest-common.cpp"

#include "testobjecttreesource.h"

#include <MimeTreeParser/ObjectTreeParser>
#include <MessageViewer/CSSHelperBase>
#include <MessageViewer/FileHtmlWriter>

#include <KMime/Message>
#include <QDir>
#include <QIcon>
#include <QPalette>
#include <QStandardPaths>
#include <QStyle>
#include <QStyleFactory>
#include <QTest>

#ifndef Q_OS_WIN
void initLocale()
{
    setenv("KDEHOME", QFile::encodeName(QDir::homePath() + QLatin1String(
                                            "/.qttest")).constData(), 1);
    setenv("LC_ALL", "en_US.utf-8", 1);
    setenv("TZ", "UTC", 1);
    setenv("BPF_ITINERARY_NO_AKONADI", "1", 1); // avoid itinerary plugin doing calendar lookups
    QStandardPaths::setTestModeEnabled(true);
    QLocale::setDefault(QLocale(QStringLiteral("en_US")));
}

Q_CONSTRUCTOR_FUNCTION(initLocale)
#endif

void RenderTest::initTestCase()
{
    QIcon::setThemeName(QStringLiteral("breeze"));
    QApplication::setStyle(QStyleFactory::create(QStringLiteral("Fusion")));
    QPalette p(QApplication::style()->standardPalette());
    p.setCurrentColorGroup(QPalette::Normal);
    p.setColor(QPalette::Button, QColor::fromRgb(0xef, 0xeb, 0xe7));
    p.setColor(QPalette::ButtonText, QColor::fromRgb(0, 0, 0));
    p.setColor(QPalette::Shadow, QColor::fromRgb(0x76, 0x74, 0x72));
    QApplication::setPalette(p);
}

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
        QTest::newRow(file.toLatin1().constData()) << QString(dir.path() + QLatin1Char('/') +  file) << QString(dir.path() + QLatin1Char('/') + file + QStringLiteral(".html"))
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
    MessageViewer::FileHtmlWriter fileWriter(outFileName);
    QImage paintDevice;
    MessageViewer::CSSHelperBase cssHelper(&paintDevice);
    MimeTreeParser::NodeHelper nodeHelper;
    TestObjectTreeSource testSource(&fileWriter, &cssHelper);
    MimeTreeParser::ObjectTreeParser otp(&testSource, &nodeHelper);

    otp.parseObjectTree(msg.data());

    fileWriter.begin();
    fileWriter.write(QStringLiteral("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
                                    "<html>\n"
                                    "<body>\n"));
    testSource.render(otp.parsedPart(), false);
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
    MessageViewer::FileHtmlWriter fileWriter(outFileName);
    QImage paintDevice;
    MessageViewer::CSSHelperBase cssHelper(&paintDevice);
    MimeTreeParser::NodeHelper nodeHelper;
    TestObjectTreeSource testSource(&fileWriter, &cssHelper);
    testSource.setShowSignatureDetails(true);
    MimeTreeParser::ObjectTreeParser otp(&testSource, &nodeHelper);

    connect(&nodeHelper, &MimeTreeParser::NodeHelper::update, &loop, &QEventLoop::quit);
    otp.parseObjectTree(msg.data());

    fileWriter.begin();
    fileWriter.write(QStringLiteral("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
                                    "<html>\n"
                                    "<body>\n"));
    testSource.render(otp.parsedPart(), false);
    fileWriter.write(QStringLiteral("</body></html>"));
    fileWriter.end();

    compareFile(outFileName, referenceFileName + QStringLiteral(".running"));
    loop.exec();

    {
        MimeTreeParser::ObjectTreeParser otp(&testSource, &nodeHelper);
        otp.parseObjectTree(msg.data());

        fileWriter.begin();
        fileWriter.write(QStringLiteral("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
                                        "<html>\n"
                                        "<body>\n"));
        testSource.render(otp.parsedPart(), false);
        fileWriter.write(QStringLiteral("</body></html>"));
        fileWriter.end();

        compareFile(outFileName, referenceFileName + QStringLiteral(".details"));
    }
}

QTEST_MAIN(RenderTest)
