/*
   Copyright (C) 2016 Montel Laurent <montel@kde.org>

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

#ifndef SELECTIMAPWIDGET_H
#define SELECTIMAPWIDGET_H

#include <QWidget>
#include <KSieveUi/SieveAccount>
#include <KSieveUi/AbstractMoveImapFolderWidget>
class QToolButton;
class KLineEdit;
class SelectImapWidget : public KSieveUi::AbstractMoveImapFolderWidget
{
    Q_OBJECT
public:
    explicit SelectImapWidget(QWidget *parent = Q_NULLPTR, const QList<QVariant> & = QList<QVariant>());
    ~SelectImapWidget();

    void setText(const QString &str) Q_DECL_OVERRIDE;
    QString text() const Q_DECL_OVERRIDE;

    void setSieveAccount(const KSieveUi::SieveAccount &account) Q_DECL_OVERRIDE;

private:
    void slotOpenSelectImapFolder();
    KSieveUi::SieveAccount mAccount;
    QToolButton *mToolButton;
    KLineEdit *mLineEdit;
};

#endif // SELECTIMAPWIDGET_H
