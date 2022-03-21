/*
  This file is part of KAddressBook.
  SPDX-FileCopyrightText: 2009 Tobias Koenig <tokoe@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KAddressBookImportExport/ContactFields>

#include <QDialog>

#include <QList>

class QComboBox;
class QLineEdit;
class KUrlRequester;

class QButtonGroup;
class QCheckBox;
class QCsvModel;
class QTableView;

class CSVImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CSVImportDialog(QWidget *parent = nullptr);
    ~CSVImportDialog() override;

    KContacts::AddresseeList contacts() const;

private:
    void setFile(const QString &);
    void setUrl(const QUrl &);
    void urlChanged(const QString &);

    void customDelimiterChanged();
    void customDelimiterChanged(const QString &, bool reload = true);
    void delimiterClicked(int, bool reload = true);
    void textQuoteChanged(const QString &, bool reload = true);
    void skipFirstRowChanged(bool, bool reload = true);
    void codecChanged(bool reload = true);

    void modelFinishedLoading();
    void finalizeApplyTemplate();

    void slotSaveTemplate();
    void slotApplyTemplate();
    void slotOk();

private:
    void applyTemplate();
    void saveTemplate();

    QTableView *mTable = nullptr;
    QButtonGroup *mDelimiterGroup = nullptr;
    QLineEdit *mDelimiterEdit = nullptr;
    QLineEdit *mDatePatternEdit = nullptr;
    QComboBox *mComboQuote = nullptr;
    QComboBox *mCodecCombo = nullptr;
    QCheckBox *mSkipFirstRow = nullptr;
    KUrlRequester *mUrlRequester = nullptr;
    QCsvModel *mModel = nullptr;

    void initGUI();

    void reloadCodecs();
    QList<QTextCodec *> mCodecs;

    QChar mTextQuote;
    QString mDelimiter;
    QMap<QString, uint> mTypeMap;
    QIODevice *mDevice = nullptr;
    KAddressBookImportExport::ContactFields::Fields mFieldSelection;
    QPushButton *mUser1Button = nullptr;
    QPushButton *mUser2Button = nullptr;
    QPushButton *mOkButton = nullptr;
};
