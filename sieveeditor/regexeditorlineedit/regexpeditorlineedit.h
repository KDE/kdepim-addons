/*
   Copyright (C) 2017 Montel Laurent <montel@kde.org>

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

#ifndef REGEXPEDITORLINEEDIT_H
#define REGEXPEDITORLINEEDIT_H

#include <QWidget>
#include <KSieveUi/AbstractRegexpEditorLineEdit>
class QLineEdit;
class QPushButton;
class RegexpEditorLineEdit : public KSieveUi::AbstractRegexpEditorLineEdit
{
    Q_OBJECT
public:
    explicit RegexpEditorLineEdit(QWidget *parent = nullptr, const QList<QVariant> & = {});
    ~RegexpEditorLineEdit();

    void switchToRegexpEditorLineEdit(bool regexpEditor) Q_DECL_OVERRIDE;
    void setCode(const QString &str) Q_DECL_OVERRIDE;
    QString code() const Q_DECL_OVERRIDE;

private:
    void slotOpenRegexpEditor();
    QLineEdit *mLineEdit;
    QPushButton *mRegExpEditorButton;
    bool mIsRegExpMode;
    bool mRegexEditorInstalled;
};

#endif // REGEXPEDITORLINEEDIT_H
