/*
   SPDX-FileCopyrightText: 2026 Volker Krause <vkrause@kde.org>
   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <QObject>
#include <QTest>

#include "../calendar/itipformatter.h"

#include <MessageViewer/MessagePartRendererManager>

#include <KCalendarCore/ICalFormat>
#include <KCalendarCore/MemoryCalendar>
#include <KCalendarCore/ScheduleMessage>

#include <QProcess>
#include <QStandardPaths>

using namespace Qt::Literals;

#ifndef Q_OS_WIN
static void initLocale()
{
    setenv("LC_ALL", "en_US.utf-8", 1);
    setenv("TZ", "UTC", 1);
}

Q_CONSTRUCTOR_FUNCTION(initLocale)
#endif

// Button colors.
static QString btnBg;
static QString btnFg;
static QString btnBdr;
static QString btnHl;

static bool validateHtml(const QString &name, const QString &_html)
{
    const QString html = QStringLiteral(
                             "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
                             "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                             "  <head>\n"
                             "    <title></title>\n"
                             "    <style></style>\n"
                             "  </head>\n"
                             "<body>")
        + _html + QStringLiteral("</body>\n</html>");

    const QString outFileName = QStringLiteral(MAIL_DATA_DIR "/../itip/%1.out").arg(name);
    const QString htmlFileName = QStringLiteral(MAIL_DATA_DIR "/../itip/%1.out.html").arg(name);
    QFile outFile(outFileName);
    if (!outFile.open(QIODevice::WriteOnly)) {
        return false;
    }
    outFile.write(html.toUtf8());
    outFile.close();

    // validate xml and pretty-print for comparison
    // TODO add proper cmake check for xmllint and diff
    const QStringList args =
        {QStringLiteral("--format"), QStringLiteral("--encode"), QStringLiteral("UTF8"), QStringLiteral("--output"), htmlFileName, outFileName};

    const int result = QProcess::execute(QStringLiteral("xmllint"), args);
    return result == 0;
}

static bool compareHtml(const QString &name)
{
    const QString htmlFileName = QStringLiteral(MAIL_DATA_DIR "/../itip/%1.out.html").arg(name);
    const QString referenceFileName = QStringLiteral(MAIL_DATA_DIR "/../itip/%1.html").arg(name);

    // get rid of system dependent or random paths
    {
        QFile f(htmlFileName);
        if (!f.open(QIODevice::ReadOnly)) {
            return false;
        }
        QString content = QString::fromUtf8(f.readAll());
        f.close();
        // clazy:excludeall=use-static-qregularexpression
        content.replace(QRegularExpression(QStringLiteral("\"file:[^\"]*[/(?:%2F)]([^\"/(?:%2F)]*)\"")), QStringLiteral("\"file:\\1\""));
        // since KF 6.3 we can also get icons with qrc paths
        content.replace(QRegularExpression(QStringLiteral("src=\"qrc:/[^\"]*[/(?:%2F)]([^\"/(?:%2F)]*)\"")), QStringLiteral("src=\"file:\\1\""));
        // icon filename extensions depend on used theme, Oxygen has PNG, Breeze has SVG
        content.replace(QRegularExpression(QStringLiteral(".(png|svg)\"")), QStringLiteral("\""));
        if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            return false;
        }
        f.write(content.toUtf8());
        f.close();
    }

#ifdef Q_OS_WIN
    const QStringList args = {
        u"Compare-Object"_s,
        u"(Get-Content %1)"_s.arg(referenceFileName),
        u"(Get-Content %1)"_s.arg(htmlFileName),
    };

    QProcess proc;
    proc.start(u"powershell"_s, args);
    if (!proc.waitForFinished()) {
        return false;
    }

    auto pStdOut = proc.readAllStandardOutput();
    if (pStdOut.size()) {
        qDebug() << "Files are different, diff output message:\n" << pStdOut;
    }

    return pStdOut.size() == 0;
#else
    // compare to reference file
    const QStringList args = {u"-u"_s, referenceFileName, htmlFileName};

    QProcess proc;
    proc.setProcessChannelMode(QProcess::ForwardedChannels);
    proc.start(u"diff"_s, args);
    if (!proc.waitForFinished()) {
        return false;
    }

    return proc.exitCode() == 0;
#endif
}

class ItipFormatterTest : public QObject
{
    Q_OBJECT
private Q_SLOTS:
    void initTestCase()
    {
        QStandardPaths::setTestModeEnabled(true);
        QIcon::setThemeName(QStringLiteral("breeze"));
        QLocale::setDefault(QLocale(QStringLiteral("en_US")));

        QPalette palette;
        palette.setCurrentColorGroup(QPalette::Normal);
        btnBg = palette.color(QPalette::Button).name();
        btnBdr = palette.shadow().color().name();
        btnFg = palette.color(QPalette::ButtonText).name();
        palette.setCurrentColorGroup(QPalette::Active);
        btnHl = palette.shadow().color().name();
    }

    void testFormatter_data()
    {
        QTest::addColumn<QString>("name");

        QTest::newRow("itip-journal") << QStringLiteral("itip-journal");
        QTest::newRow("itip-journal-delegation-request") << QStringLiteral("itip-journal-delegation-request");
        QTest::newRow("itip-journal-delegation-reply") << QStringLiteral("itip-journal-delegation-reply");
        QTest::newRow("itip-journal-declined-reply") << QStringLiteral("itip-journal-declined-reply");
        QTest::newRow("itip-journal-tentative-reply") << QStringLiteral("itip-journal-tentative-reply");
        QTest::newRow("itip-journal-accepted-reply") << QStringLiteral("itip-journal-accepted-reply");

        QTest::newRow("itip-todo") << QStringLiteral("itip-todo");
        QTest::newRow("itip-todo-with-start") << QStringLiteral("itip-todo-with-start");
        QTest::newRow("itip-todo-delegation-request") << QStringLiteral("itip-todo-delegation-request");
        QTest::newRow("itip-todo-delegation-reply") << QStringLiteral("itip-todo-delegation-reply");
        QTest::newRow("itip-todo-declined-reply") << QStringLiteral("itip-todo-declined-reply");
        QTest::newRow("itip-todo-tentative-reply") << QStringLiteral("itip-todo-tentative-reply");
        QTest::newRow("itip-todo-accepted-reply") << QStringLiteral("itip-todo-accepted-reply");

        QTest::newRow("itip-event-with-html-description") << QStringLiteral("itip-event-with-html-description");
        QTest::newRow("itip-event-with-recurrence-attachment-reminder") << QStringLiteral("itip-event-with-recurrence-attachment-reminder");
        QTest::newRow("itip-event-multiday-allday") << QStringLiteral("itip-event-multiday-allday");
        QTest::newRow("itip-event-multiday") << QStringLiteral("itip-event-multiday");
        QTest::newRow("itip-event-allday") << QStringLiteral("itip-event-allday");
        QTest::newRow("itip-event") << QStringLiteral("itip-event");
        QTest::newRow("itip-event-request") << QStringLiteral("itip-event-request");
        QTest::newRow("itip-event-counterproposal") << QStringLiteral("itip-event-counterproposal");
        QTest::newRow("itip-event-counterproposal-declined") << QStringLiteral("itip-event-counterproposal-declined");
        QTest::newRow("itip-event-delegation-request") << QStringLiteral("itip-event-delegation-request");
        QTest::newRow("itip-event-delegation-reply") << QStringLiteral("itip-event-delegation-reply");
        QTest::newRow("itip-event-declined-reply") << QStringLiteral("itip-event-delegation-reply");
        QTest::newRow("itip-event-tentative-reply") << QStringLiteral("itip-event-tentative-reply");
        QTest::newRow("itip-event-accepted-reply") << QStringLiteral("itip-event-accepted-reply");
    }

    void testFormatter()
    {
        QFETCH(const QString, name);

        const KCalendarCore::MemoryCalendar::Ptr calendar(new KCalendarCore::MemoryCalendar(QTimeZone::utc()));
        InvitationFormatterHelper helper;

        QFile eventFile(QStringLiteral(MAIL_DATA_DIR "/../itip/%1.ical").arg(name));
        QVERIFY(eventFile.exists());
        QVERIFY(eventFile.open(QIODevice::ReadOnly));
        const QByteArray data = eventFile.readAll();

        KCalendarCore::ICalFormat format;
#if KCALENDARCORE_VERSION < QT_VERSION_CHECK(6, 30, 0)
        const KCalendarCore::ScheduleMessage::Ptr message = format.parseScheduleMessage(calendar, QString::fromUtf8(data));
#else
        const KCalendarCore::ScheduleMessage::Ptr message = format.parseScheduleMessage(calendar, data);
#endif
        QVERIFY(message);

        const QString html = ItipFormatter::formatICalInvitation(message, &helper, QString())
                                 .replace(btnBg, QStringLiteral("btnBg"))
                                 .replace(btnFg, QStringLiteral("btnFg"))
                                 .replace(btnBdr, QStringLiteral("btnBdr"));

        QVERIFY(validateHtml(name, html));
        QVERIFY(compareHtml(name));

        QFile::remove(QStringLiteral(MAIL_DATA_DIR "/../itip/%1.out").arg(name));
        QFile::remove(QStringLiteral(MAIL_DATA_DIR "/../itip/%1.out.html").arg(name));
    }
};

QTEST_MAIN(ItipFormatterTest)

#include "itipformattertest.moc"
