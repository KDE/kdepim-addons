/*
   SPDX-FileCopyrightText: 2018-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <Akonadi/ServerManager>
#include <KContacts/Addressee>
#include <KSieveUi/AbstractSelectEmailLineEdit>
class QLineEdit;
class QToolButton;
class EmailLineEdit : public KSieveUi::AbstractSelectEmailLineEdit
{
    Q_OBJECT
public:
    explicit EmailLineEdit(QWidget *parent = nullptr, const QList<QVariant> & = {});
    ~EmailLineEdit() override;

    void setText(const QString &str) override;
    [[nodiscard]] QString text() const override;
    [[nodiscard]] bool isValid() const override;

private:
    void insertAddresses(const KContacts::Addressee::List &list);
    void slotTextChanged();
    void verifyAddress();
    void slotSelectEmail();
    void verifyAkonadiStatus();
    void akonadiStateChanged(Akonadi::ServerManager::State state);
    QString mNegativeBackground;
    QLineEdit *const mLineEdit;
    QToolButton *const mEmailButton;
    bool mEmailIsValid = false;
};
