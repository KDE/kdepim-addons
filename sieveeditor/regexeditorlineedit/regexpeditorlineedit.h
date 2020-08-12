/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef REGEXPEDITORLINEEDIT_H
#define REGEXPEDITORLINEEDIT_H

#include <QWidget>
#include <KSieveUi/AbstractRegexpEditorLineEdit>
class QLineEdit;
class QToolButton;
class RegexpEditorLineEdit : public KSieveUi::AbstractRegexpEditorLineEdit
{
    Q_OBJECT
public:
    explicit RegexpEditorLineEdit(QWidget *parent = nullptr, const QList<QVariant> & = {
    });
    ~RegexpEditorLineEdit() override;

    void switchToRegexpEditorLineEdit(bool regexpEditor) override;
    void setCode(const QString &str) override;
    QString code() const override;
    void setClearButtonEnabled(bool b) override;
    void setPlaceholderText(const QString &str) override;

private:
    void slotOpenRegexpEditor();
    QLineEdit *mLineEdit = nullptr;
    QToolButton *mRegExpEditorButton = nullptr;
};

#endif // REGEXPEDITORLINEEDIT_H
