/*
  SPDX-FileCopyrightText: 2010 Volker Krause <vkrause@kde.org>
  SPDX-FileCopyrightText: 2016 Sandro Knauß <sknauss@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "rendertest.h"
#include "rendertest-common.cpp"

#include "testobjecttreesource.h"

#include <MessageViewer/CSSHelperBase>
#include <MessageViewer/FileHtmlWriter>
#include <MimeTreeParser/ObjectTreeParser>

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
    setenv("KDEHOME", QFile::encodeName(QDir::homePath() + QLatin1StringView("/.qttest")).constData(), 1);
    setenv("LC_ALL", "en_US.utf-8", 1);
    setenv("TZ", "UTC", 1);
    setenv("BPF_ITINERARY_TESTMODE", "1", 1); // avoid itinerary plugin doing calendar lookups or D-Bus calls etc
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
        QTest::newRow(file.toLatin1().constData()) << QString(dir.path() + QLatin1Char('/') + file)
                                                   << QString(dir.path() + QLatin1Char('/') + file + QStringLiteral(".html"))
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
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    msg->setContent(mailData);
    msg->parse();

    // render the mail
    MessageViewer::FileHtmlWriter fileWriter(outFileName);
    QImage paintDevice;
    MessageViewer::CSSHelperBase cssHelper(&paintDevice);
    MimeTreeParser::NodeHelper nodeHelper;
    TestObjectTreeSource testSource(&fileWriter, &cssHelper);
    MimeTreeParser::ObjectTreeParser otp(&testSource, &nodeHelper);

    otp.parseObjectTree(msg.get());

    fileWriter.begin();
    fileWriter.write(
        QStringLiteral("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
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
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
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
    otp.parseObjectTree(msg.get());

    fileWriter.begin();
    fileWriter.write(
        QStringLiteral("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
                       "<html>\n"
                       "<body>\n"));
    testSource.render(otp.parsedPart(), false);
    fileWriter.write(QStringLiteral("</body></html>"));
    fileWriter.end();

    compareFile(outFileName, referenceFileName + QStringLiteral(".running"));
    loop.exec();

    {
        MimeTreeParser::ObjectTreeParser otp(&testSource, &nodeHelper);
        otp.parseObjectTree(msg.get());

        fileWriter.begin();
        fileWriter.write(
            QStringLiteral("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n"
                           "<html>\n"
                           "<body>\n"));
        testSource.render(otp.parsedPart(), false);
        fileWriter.write(QStringLiteral("</body></html>"));
        fileWriter.end();

        compareFile(outFileName, referenceFileName + QStringLiteral(".details"));
    }
}

QTEST_MAIN(RenderTest)

#include "moc_rendertest.cpp"
