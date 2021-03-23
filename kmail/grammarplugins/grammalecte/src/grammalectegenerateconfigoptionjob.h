/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libgrammalect_private_export.h"
#include <QObject>
#include <QProcess>
#include <QVector>

class LIBGRAMMALECTPRIVATE_TESTS_EXPORT GrammalecteGenerateConfigOptionJob : public QObject
{
    Q_OBJECT
public:
    struct Option {
        QString optionName;
        QString description;
        bool defaultValue = false;
    };

    explicit GrammalecteGenerateConfigOptionJob(QObject *parent = nullptr);
    ~GrammalecteGenerateConfigOptionJob() override;

    void start();
    Q_REQUIRED_RESULT bool canStart() const;

    Q_REQUIRED_RESULT QString pythonPath() const;
    void setPythonPath(const QString &pythonPath);

    Q_REQUIRED_RESULT QString grammarlecteCliPath() const;
    void setGrammarlecteCliPath(const QString &grammarlecteCliPath);

Q_SIGNALS:
    void error();
    void finished(const QVector<GrammalecteGenerateConfigOptionJob::Option> &result);

private:
    Q_DISABLE_COPY(GrammalecteGenerateConfigOptionJob)
    void receivedStandardOutput();
    void slotFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void receivedError();
    void receivedStdErr();
    QVector<GrammalecteGenerateConfigOptionJob::Option> parseResult() const;
    QString mResult;
    QString mPythonPath;
    QString mGrammarlecteCliPath;
    QString mLastError;
    QProcess *mProcess = nullptr;
};
Q_DECLARE_TYPEINFO(GrammalecteGenerateConfigOptionJob::Option, Q_MOVABLE_TYPE);
