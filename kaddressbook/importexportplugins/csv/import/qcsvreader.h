/*
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

#include <memory>
class QTextCodec;

class QIODevice;

/**
 * @short An interface to build data structures from a CSV file.
 *
 * This class provides an abstract interface that can be used
 * to build up data structures from a comma separated value file
 * that is parsed with QCsvReader.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class QCsvBuilderInterface
{
public:
    /**
     * This method is called on the destruction of the interface.
     */
    virtual ~QCsvBuilderInterface();

    /**
     * This method is called on start of the parsing.
     */
    virtual void begin() = 0;

    /**
     * This method is called whenever a new line starts.
     */
    virtual void beginLine() = 0;

    /**
     * This method is called for every parsed field.
     *
     * @param data The data of the field.
     * @param row The row of the field.
     * @param column The column of the field.
     */
    virtual void field(const QString &data, uint row, uint column) = 0;

    /**
     * This method is called whenever a line ends.
     */
    virtual void endLine() = 0;

    /**
     * This method is called at the end of parsing.
     */
    virtual void end() = 0;

    /**
     * This method is called whenever an error occurs during parsing.
     *
     * @param errorMsg The error message.
     */
    virtual void error(const QString &errorMsg) = 0;
};

class QCsvReaderPrivate;

/**
 * @short A parser for comma separated value data.
 *
 * QCsvReader is a class that reads a comma separated value list (csv)
 * from a device and parses it into its fields. The parsed data are
 * passed to a QCsvBuilderInterface instance, which can build up
 * arbitrary data structures from it.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class QCsvReader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QChar textQuote READ textQuote WRITE setTextQuote)
    Q_PROPERTY(QChar delimiter READ delimiter WRITE setDelimiter)
    Q_PROPERTY(uint startRow READ startRow WRITE setStartRow)

public:
    /**
     * Creates a new csv reader.
     *
     * @param builder The builder to use.
     */
    explicit QCsvReader(QCsvBuilderInterface *builder);

    /**
     * Destroys the csv reader.
     */
    ~QCsvReader() override;

    /**
     * Parses the csv data from @p device.
     *
     * @return true on success, false otherwise.
     */
    bool read(QIODevice *device);

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
     * Terminates the parsing of the csv data.
     */
    void terminate();

private:
    std::unique_ptr<QCsvReaderPrivate> const d;
};

class QCsvStandardBuilderPrivate;

/**
 * @short A convenience class that implements QCsvBuilderInterface.
 *
 * QCsvStandardBuilder is a convenience class which stores
 * the parsed data from a csv list.
 *
 * @author Tobias Koenig <tokoe@kde.org>
 */
class QCsvStandardBuilder : public QCsvBuilderInterface
{
public:
    /**
     * Creates a new csv standard builder.
     */
    QCsvStandardBuilder();

    /**
     * Destroys the csv standard builder.
     */
    ~QCsvStandardBuilder() override;

    /**
     * Returns the error message of the last error.
     */
    QString lastErrorString() const;

    /**
     * Returns the number of rows.
     */
    uint rowCount() const;

    /**
     * Returns the number of columns.
     */
    uint columnCount() const;

    /**
     * Returns the data of the field at the given
     * @p row and @p column.
     */
    QString data(uint row, uint column) const;

    /**
     * @internal
     */
    void begin() override;
    void beginLine() override;
    void field(const QString &data, uint row, uint column) override;
    void endLine() override;
    void end() override;
    void error(const QString &errorMsg) override;

private:
    std::unique_ptr<QCsvStandardBuilderPrivate> const d;

    Q_DISABLE_COPY(QCsvStandardBuilder)
};
