/*
    SPDX-FileCopyrightText: 2007 Volker Krause <vkrause@kde.org>
    SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

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

    [[nodiscard]] QString delegate() const;
    [[nodiscard]] bool rsvp() const;

private:
    void slotTextChanged(const QString &text);
    PimCommon::AddresseeLineEdit *const mDelegate;
    QCheckBox *const mRsvp;
    QPushButton *mOkButton = nullptr;
};
