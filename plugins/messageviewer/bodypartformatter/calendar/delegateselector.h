/*
    SPDX-FileCopyrightText: 2007 Volker Krause <vkrause@kde.org>
    SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DELEGATESELECTOR_H
#define DELEGATESELECTOR_H

#include <QDialog>
class QPushButton;
namespace PimCommon
{
class AddresseeLineEdit;
}

class QCheckBox;

/**
  Selection dialog for a delegate.
*/
class DelegateSelector : public QDialog
{
    Q_OBJECT

public:
    explicit DelegateSelector(QWidget *parent = nullptr);

    Q_REQUIRED_RESULT QString delegate() const;
    Q_REQUIRED_RESULT bool rsvp() const;

private:
    void slotTextChanged(const QString &text);
    PimCommon::AddresseeLineEdit *mDelegate = nullptr;
    QCheckBox *mRsvp = nullptr;
    QPushButton *mOkButton = nullptr;
};

#endif
