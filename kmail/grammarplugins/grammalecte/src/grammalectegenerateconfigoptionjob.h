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

#ifndef GRAMMALECTEGENERATECONFIGOPTIONJOB_H
#define GRAMMALECTEGENERATECONFIGOPTIONJOB_H

#include <QObject>
#include <QProcess>
#include <QVector>
#include "libgrammalect_private_export.h"

class LIBGRAMMALECTPRIVATE_TESTS_EXPORT GrammalecteGenerateConfigOptionJob : public QObject
{
    Q_OBJECT
public:

    struct Option
    {
        QString optionName;
        QString description;
        bool defaultValue = false;
    };

    explicit GrammalecteGenerateConfigOptionJob(QObject *parent = nullptr);
    ~GrammalecteGenerateConfigOptionJob();

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
#endif // GRAMMALECTEGENERATECONFIGOPTIONJOB_H
