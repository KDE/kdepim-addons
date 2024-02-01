/*
   SPDX-FileCopyrightText: 2018 Sandro Knauß <sknauss@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "utils.h"
#include <MessageViewer/HeaderStyle>
#include <QFile>
#include <QProcess>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QTest>

void testHeaderFile(const QString &data, const QString &name, const QString &dir)
{
    QString header = QStringLiteral(
        "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
        "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
        "<body>\n");
    header += data;
    header += QStringLiteral("\n</body>\n</html>\n");

    QString imagePath(QStandardPaths::locate(QStandardPaths::GenericDataLocation, QStringLiteral("libmessageviewer/pics"), QStandardPaths::LocateDirectory));
    header.replace(QStringLiteral("file://") + imagePath, QStringLiteral("file://PATHTOIMAGES"));
    header.replace(QRegularExpression(QStringLiteral("[\t ]+")), QStringLiteral(" "));
    header.replace(QRegularExpression(QStringLiteral("[\t ]*\n+[\t ]*")), QStringLiteral("\n"));
    header.replace(QRegularExpression(QStringLiteral("([\n\t ])\\1+")), QStringLiteral("\\1"));
    header.replace(QRegularExpression(QStringLiteral(">\n+[\t ]*")), QStringLiteral(">"));
    header.replace(QRegularExpression(QStringLiteral("[\t ]*\n+[\t ]*<")), QStringLiteral("<"));
    header.replace(QLatin1StringView("&nbsp;"), QLatin1StringView("NBSP_ENTITY_PLACEHOLDER")); // xmlling chokes on &nbsp;

    QString outName = name + QStringLiteral(".out.html");
    QString fName = name + QStringLiteral(".html");

    QString referenceFile = QStringLiteral(HEADER_DATA_DIR "/");
    if (!dir.isEmpty()) {
        referenceFile += dir + QStringLiteral("/");
    }
    referenceFile += fName;

    QVERIFY(QFile(referenceFile).exists());

    {
        QFile f(outName);
        f.open(QIODevice::WriteOnly);
        f.write(header.toUtf8());
        f.close();
    }
    // TODO add proper cmake check for xmllint and diff
    {
        const QStringList args = QStringList() << QStringLiteral("--format") << QStringLiteral("--encode") << QStringLiteral("UTF8")
                                               << QStringLiteral("--output") << fName << outName;
        QCOMPARE(QProcess::execute(QStringLiteral("xmllint"), args), 0);
    }

    {
        // compare to reference file
        const QStringList args = QStringList() << QStringLiteral("-u") << fName << referenceFile;
        QProcess proc;
        proc.setProcessChannelMode(QProcess::ForwardedChannels);
        proc.start(QStringLiteral("diff"), args);
        QVERIFY(proc.waitForFinished());

        QCOMPARE(proc.exitCode(), 0);
    }
}

KMime::Message::Ptr readAndParseMail(const QString &mailFile)
{
    QFile file(QStringLiteral(HEADER_DATA_DIR) + QLatin1Char('/') + mailFile);
    bool openFile = file.open(QIODevice::ReadOnly);
    Q_ASSERT(openFile);
    const QByteArray data = KMime::CRLFtoLF(file.readAll());
    Q_ASSERT(!data.isEmpty());
    KMime::Message::Ptr msg(new KMime::Message);
    msg->setContent(data);
    msg->parse();
    return msg;
}
