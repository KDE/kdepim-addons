/*
   Copyright (C) 2018-2019 Montel Laurent <montel@kde.org>

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

#ifndef EMAILLINEEDIT_H
#define EMAILLINEEDIT_H

#include <KSieveUi/AbstractSelectEmailLineEdit>
#include <AkonadiCore/ServerManager>
class QLineEdit;
class QToolButton;
class EmailLineEdit : public KSieveUi::AbstractSelectEmailLineEdit
{
    Q_OBJECT
public:
    explicit EmailLineEdit(QWidget *parent = nullptr, const QList<QVariant> & =
    {
    });
    ~EmailLineEdit() override;

    void setText(const QString &str) override;
    QString text() const override;
    bool isValid() const override;
private:
    void slotTextChanged();
    void verifyAddress();
    void slotSelectEmail();
    void verifyAkonadiStatus();
    void akonadiStateChanged(Akonadi::ServerManager::State state);
    QString mNegativeBackground;
    QLineEdit *mLineEdit = nullptr;
    QToolButton *mEmailButton = nullptr;
    bool mEmailIsValid = false;
};

#endif // EMAILLINEEDIT_H
