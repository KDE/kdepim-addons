/*
   Copyright (C) 2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef GRAMMARRESULTJOB_H
#define GRAMMARRESULTJOB_H

#include <QObject>
#include <QProcess>
#include "libgrammalect_private_export.h"
class LIBGRAMMALECTPRIVATE_TESTS_EXPORT GrammalecteResultJob : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteResultJob(QObject *parent = nullptr);
    ~GrammalecteResultJob();

    enum class ErrorType {
        NoError = 0,
        TextIsEmpty = 1,
        PythonPathMissing = 2,
        GrammalecteMissing = 3,
        Unknown = 4,
    };

    void start();

    Q_REQUIRED_RESULT bool canStart();

    Q_REQUIRED_RESULT QString text() const;
    void setText(const QString &text);

    Q_REQUIRED_RESULT QString pythonPath() const;
    void setPythonPath(const QString &pythonPath);

    Q_REQUIRED_RESULT QString grammarlecteCliPath() const;
    void setGrammarlecteCliPath(const QString &grammarlecteCliPath);

    Q_REQUIRED_RESULT QStringList arguments() const;
    void setArguments(const QStringList &arguments);

Q_SIGNALS:
    void finished(const QString &result);
    void error(GrammalecteResultJob::ErrorType type);

private:
    Q_DISABLE_COPY(GrammalecteResultJob)
    void slotFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void receivedStdErr();
    void receivedError();
    void receivedStandardOutput();
    QStringList mArguments;
    QString mResult;
    QString mText;
    QString mPythonPath;
    QString mGrammarlecteCliPath;
    QString mLastError;
    GrammalecteResultJob::ErrorType mErrorType = ErrorType::NoError;
    QProcess *mProcess = nullptr;
};

#endif // GRAMMARRESULTJOB_H
