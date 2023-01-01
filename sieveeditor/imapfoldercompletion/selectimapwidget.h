/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KSieveUi/AbstractMoveImapFolderWidget>
#include <KSieveUi/SieveImapAccountSettings>
#include <QPointer>
class QWidget;
class QToolButton;
class SelectImapLineEdit;
class SelectImapFolderDialog;
class SelectImapWidget : public KSieveUi::AbstractMoveImapFolderWidget
{
    Q_OBJECT
public:
    explicit SelectImapWidget(QWidget *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~SelectImapWidget() override;

    void setText(const QString &str) override;
    Q_REQUIRED_RESULT QString text() const override;

    void setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account) override;

private:
    void slotOpenSelectImapFolder();
    SelectImapFolderDialog *selectFolderDialog();
    KSieveUi::SieveImapAccountSettings mAccount;
    QPointer<SelectImapFolderDialog> mSelectImapFolderDialog;
    QToolButton *const mToolButton;
    SelectImapLineEdit *const mLineEdit;
};
