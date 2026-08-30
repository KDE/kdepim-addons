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
using namespace Qt::Literals::StringLiterals;

void testHeaderFile(const QString &data, const QString &name, const QString &dir)
{
    QString header =
        u"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
        "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
        "<body>\n"_s;
    header += data;
    header += u"\n</body>\n</html>\n"_s;

    QString imagePath(QStandardPaths::locate(QStandardPaths::GenericDataLocation, u"libmessageviewer/pics"_s, QStandardPaths::LocateDirectory));
    header.replace(u"file://"_s + imagePath, u"file://PATHTOIMAGES"_s);
    header.replace(QRegularExpression(u"[\t ]+"_s), u" "_s);
    header.replace(QRegularExpression(u"[\t ]*\n+[\t ]*"_s), u"\n"_s);
    header.replace(QRegularExpression(u"([\n\t ])\\1+"_s), u"\\1"_s);
    header.replace(QRegularExpression(u">\n+[\t ]*"_s), u">"_s);
    header.replace(QRegularExpression(u"[\t ]*\n+[\t ]*<"_s), u"<"_s);
    header.replace(QLatin1StringView("&nbsp;"), QLatin1StringView("NBSP_ENTITY_PLACEHOLDER")); // xmlling chokes on &nbsp;

    QString outName = name + u".out.html"_s;
    QString fName = name + u".html"_s;

    QString referenceFile = QStringLiteral(HEADER_DATA_DIR "/");
    if (!dir.isEmpty()) {
        referenceFile += dir + u"/"_s;
    }
    referenceFile += fName;

    QVERIFY(QFile(referenceFile).exists());

    {
        QFile f(outName);
        QVERIFY(f.open(QIODevice::WriteOnly));
        f.write(header.toUtf8());
        f.close();
    }
    // TODO add proper cmake check for xmllint and diff
    {
        const QStringList args = QStringList() << u"--format"_s << u"--encode"_s << u"UTF8"_s << u"--output"_s << fName << outName;
        QCOMPARE(QProcess::execute(u"xmllint"_s, args), 0);
    }

    {
        // compare to reference file
        const QStringList args = QStringList() << u"-u"_s << fName << referenceFile;
        QProcess proc;
        proc.setProcessChannelMode(QProcess::ForwardedChannels);
        proc.start(u"diff"_s, args);
        QVERIFY(proc.waitForFinished());

        QCOMPARE(proc.exitCode(), 0);
    }
}

std::shared_ptr<KMime::Message> readAndParseMail(const QString &mailFile)
{
    QFile file(QStringLiteral(HEADER_DATA_DIR) + QLatin1Char('/') + mailFile);
    bool openFile = file.open(QIODevice::ReadOnly);
    Q_ASSERT(openFile);
    const QByteArray data = KMime::CRLFtoLF(file.readAll());
    Q_ASSERT(!data.isEmpty());
    std::shared_ptr<KMime::Message> msg(new KMime::Message);
    msg->setContent(data);
    msg->parse();
    return msg;
}
