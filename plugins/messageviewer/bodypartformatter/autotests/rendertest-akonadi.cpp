/*
  SPDX-FileCopyrightText: 2010 Volker Krause <vkrause@kde.org>
  SPDX-FileCopyrightText: 2016 Sandro Knauß <sknauss@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

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
    QStandardPaths::setTestModeEnabled(true);
    QLocale::setDefault(QLocale(QStringLiteral("en_US")));
}

Q_CONSTRUCTOR_FUNCTION(initLocale)
#endif

class RenderTestAkonadi : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase()
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

    void testRender_data()
    {
        QTest::addColumn<QString>("mailFileName");
        QTest::addColumn<QString>("referenceFileName");
        QTest::addColumn<QString>("outFileName");

        QDir dir(QStringLiteral(DATA_DIR));
        const QStringList lst = dir.entryList(QStringList(QStringLiteral("*.mbox")), QDir::Files | QDir::Readable | QDir::NoSymLinks);
        for (const QString &file : lst) {
            if (!QFile::exists(dir.path() + QLatin1Char('/') + file + QStringLiteral(".html"))) {
                continue;
            }
            QTest::newRow(file.toLatin1().constData())
                << QString(dir.path() + QLatin1Char('/') + file) << QString(dir.path() + QLatin1Char('/') + file + QStringLiteral(".html"))
                << QString(file + QStringLiteral(".out"));
        }
    }

    void testRender()
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
};

QTEST_MAIN(RenderTestAkonadi)

#include "rendertest-akonadi.moc"
