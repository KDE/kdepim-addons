/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KSieveCore/SieveImapAccountSettings>
#include <KSieveUi/AbstractMoveImapFolderWidget>
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
    [[nodiscard]] QString text() const override;

    void setSieveImapAccountSettings(const KSieveCore::SieveImapAccountSettings &account) override;

private:
    void slotOpenSelectImapFolder();
    SelectImapFolderDialog *selectFolderDialog();
    KSieveCore::SieveImapAccountSettings mAccount;
    QPointer<SelectImapFolderDialog> mSelectImapFolderDialog;
    QToolButton *const mToolButton;
    SelectImapLineEdit *const mLineEdit;
};
