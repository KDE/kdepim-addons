/*
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "qcsvmodel.h"
#include "qcsvmodel_p.h"
#include "qcsvreader.h"
#include <QIODevice>
#include <QPair>

CsvParser::CsvParser(QObject *parent)
    : QThread(parent)
    , mReader(new QCsvReader(this))
{
}

CsvParser::~CsvParser()
{
    delete mReader;
}

void CsvParser::load(QIODevice *device)
{
    mDevice = device;

    start();
}

void CsvParser::begin()
{
    mCacheCounter = 0;
    mRowCount = 0;
    mColumnCount = 0;
}

void CsvParser::beginLine()
{
    mRowCount++;
}

void CsvParser::field(const QString &data, uint row, uint column)
{
    const int tmp = qMax(mColumnCount, (int)column + 1);
    if (tmp != mColumnCount) {
        mColumnCount = tmp;
        Q_EMIT columnCountChanged(tmp);
    }

    Q_EMIT dataChanged(data, row, column);
}

void CsvParser::endLine()
{
    mCacheCounter++;
    if (mCacheCounter == 50) {
        Q_EMIT rowCountChanged(mRowCount);
        mCacheCounter = 0;
    }
}

void CsvParser::end()
{
    Q_EMIT rowCountChanged(mRowCount);
    Q_EMIT ended();
}

void CsvParser::error(const QString &)
{
}

void CsvParser::run()
{
    if (!mDevice->isOpen()) {
        mDevice->open(QIODevice::ReadOnly);
    }

    mDevice->reset();
    mReader->read(mDevice);
}

void QCsvModel::columnCountChanged(int columns)
{
    mColumnCount = columns;
    mFieldIdentifiers.resize(columns);
    mFieldIdentifiers[columns - 1] = QStringLiteral("0");
    Q_EMIT layoutChanged();
}

void QCsvModel::rowCountChanged(int rows)
{
    mRowCount = rows;
    Q_EMIT layoutChanged();
}

void QCsvModel::fieldChanged(const QString &data, int row, int column)
{
    mFields.insert(QPair<int, int>(row, column), data);
}

QCsvModel::QCsvModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    mParser = new CsvParser(this);

    connect(mParser, &CsvParser::columnCountChanged, this, &QCsvModel::columnCountChanged, Qt::QueuedConnection);
    connect(mParser, &CsvParser::rowCountChanged, this, &QCsvModel::rowCountChanged, Qt::QueuedConnection);
    connect(mParser, &CsvParser::dataChanged, this, &QCsvModel::fieldChanged, Qt::QueuedConnection);
    connect(mParser, &CsvParser::ended, this, &QCsvModel::finishedLoading);
}

QCsvModel::~QCsvModel() = default;

bool QCsvModel::load(QIODevice *device)
{
    mDevice = device;
    mRowCount = 0;
    mColumnCount = 0;

    Q_EMIT layoutChanged();

    mParser->load(device);

    return true;
}

void QCsvModel::setTextQuote(QChar textQuote)
{
    const bool isRunning = mParser->isRunning();

    if (isRunning) {
        mParser->reader()->terminate();
        mParser->wait();
    }

    mParser->reader()->setTextQuote(textQuote);

    if (isRunning) {
        load(mDevice);
    }
}

QChar QCsvModel::textQuote() const
{
    return mParser->reader()->textQuote();
}

void QCsvModel::setDelimiter(QChar delimiter)
{
    const bool isRunning = mParser->isRunning();

    if (isRunning) {
        mParser->reader()->terminate();
        mParser->wait();
    }

    mParser->reader()->setDelimiter(delimiter);

    if (isRunning) {
        load(mDevice);
    }
}

QChar QCsvModel::delimiter() const
{
    return mParser->reader()->delimiter();
}

void QCsvModel::setStartRow(uint startRow)
{
    const bool isRunning = mParser->isRunning();

    if (isRunning) {
        mParser->reader()->terminate();
        mParser->wait();
    }

    mParser->reader()->setStartRow(startRow);

    if (isRunning) {
        load(mDevice);
    }
}

uint QCsvModel::startRow() const
{
    return mParser->reader()->startRow();
}

void QCsvModel::setTextCodec(QTextCodec *textCodec)
{
    const bool isRunning = mParser->isRunning();

    if (isRunning) {
        mParser->reader()->terminate();
        mParser->wait();
    }

    mParser->reader()->setTextCodec(textCodec);

    if (isRunning) {
        load(mDevice);
    }
}

QTextCodec *QCsvModel::textCodec() const
{
    return mParser->reader()->textCodec();
}

int QCsvModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return mColumnCount;
    } else {
        return 0;
    }
}

int QCsvModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return mRowCount + 1; // +1 for the header row
    } else {
        return 0;
    }
}

QVariant QCsvModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    if (index.row() == 0) {
        if (index.column() >= mFieldIdentifiers.count()) {
            return {};
        }

        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            return mFieldIdentifiers.at(index.column());
        }

        return {};
    }

    const QPair<int, int> pair(index.row() - 1, index.column());
    if (!mFields.contains(pair)) {
        return {};
    }

    const QString data = mFields.value(pair);

    if (role == Qt::DisplayRole) {
        return data;
    } else {
        return {};
    }
}

bool QCsvModel::setData(const QModelIndex &index, const QVariant &data, int role)
{
    if (role == Qt::EditRole && index.row() == 0 && index.column() <= mFieldIdentifiers.count()) {
        mFieldIdentifiers[index.column()] = data.toString();

        Q_EMIT dataChanged(index, index);
        return true;
    }

    return false;
}

Qt::ItemFlags QCsvModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    if (index.row() == 0) {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

#include "moc_qcsvmodel.cpp"
#include "moc_qcsvmodel_p.cpp"
