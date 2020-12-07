/*
   SPDX-FileCopyrightText: 2019-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    ~GrammalecteResultJob() override;

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
