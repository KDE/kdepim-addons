/*
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef QCSVMODEL_P_H
#define QCSVMODEL_P_H

#include "qcsvreader.h"

#include <QThread>

class CsvParser : public QThread, public QCsvBuilderInterface
{
    Q_OBJECT

public:
    explicit CsvParser(QObject *parent);
    ~CsvParser() override;

    void load(QIODevice *device);

    void begin() override;
    void beginLine() override;
    void field(const QString &data, uint row, uint column) override;
    void endLine() override;
    void end() override;
    void error(const QString &errorMsg) override;

    QCsvReader *reader()
    {
        return mReader;
    }

Q_SIGNALS:
    void columnCountChanged(int columns);
    void rowCountChanged(int rows);
    void dataChanged(const QString &data, int row, int column);
    void ended();

protected:
    void run() override;

private:
    QCsvReader *const mReader;
    QIODevice *mDevice = nullptr;
    int mRowCount = 0;
    int mColumnCount = 0;
    int mCacheCounter = 0;
};

#endif
