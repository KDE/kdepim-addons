/*
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QAbstractTableModel>
class QIODevice;
class CsvParser;
class QTextCodec;
class QCsvModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    /**
     * Creates a new csv model.
     */
    explicit QCsvModel(QObject *parent);

    /**
     * Destroys the csv model.
     */
    ~QCsvModel() override;

    /**
     * Loads the data from the @p device into the model.
     */
    bool load(QIODevice *device);

    /**
     * Sets the character that is used for quoting. The default is '"'.
     */
    void setTextQuote(QChar textQuote);

    /**
     * Returns the character that is used for quoting.
     */
    QChar textQuote() const;

    /**
     * Sets the character that is used as delimiter for fields.
     * The default is ' '.
     */
    void setDelimiter(QChar delimiter);

    /**
     * Returns the delimiter that is used as delimiter for fields.
     */
    QChar delimiter() const;

    /**
     * Sets the row from where the parsing shall be started.
     *
     * Some csv files have some kind of header in the first line with
     * the column titles. To retrieve only the real data, set the start row
     * to '1' in this case.
     *
     * The default start row is 0.
     */
    void setStartRow(uint startRow);

    /**
     * Returns the start row.
     */
    uint startRow() const;

    /**
     * Sets the text codec that shall be used for parsing the csv list.
     *
     * The default is the system locale.
     */
    void setTextCodec(QTextCodec *textCodec);

    /**
     * Returns the text codec that is used for parsing the csv list.
     */
    QTextCodec *textCodec() const;

    /**
     * Inherited from QAbstractTableModel.
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * Inherited from QAbstractTableModel.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * Inherited from QAbstractTableModel.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * Inherited from QAbstractTableModel.
     */
    bool setData(const QModelIndex &index, const QVariant &data, int role = Qt::EditRole) override;

    /**
     * Inherited from QAbstractTableModel.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const override;

Q_SIGNALS:
    /**
     * This signal is emitted whenever the model has loaded all data.
     */
    void finishedLoading();

private Q_SLOTS:
    void columnCountChanged(int columns);
    void rowCountChanged(int rows);
    void fieldChanged(const QString &data, int row, int column);

private:
    CsvParser *mParser = nullptr;
    QList<QString> mFieldIdentifiers;
    QMap<QPair<int, int>, QString> mFields;
    QIODevice *mDevice = nullptr;

    int mRowCount = 0;
    int mColumnCount = 0;
};
