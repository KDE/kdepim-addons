/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPWIDGET_H
#define SELECTIMAPWIDGET_H

#include <QWidget>
#include <KSieveUi/SieveImapAccountSettings>
#include <KSieveUi/AbstractMoveImapFolderWidget>
#include <QPointer>
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
    QString text() const override;

    void setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account) override;

private:
    void slotOpenSelectImapFolder();
    SelectImapFolderDialog *selectFolderDialog();
    KSieveUi::SieveImapAccountSettings mAccount;
    QPointer<SelectImapFolderDialog> mSelectImapFolderDialog;
    QToolButton *mToolButton = nullptr;
    SelectImapLineEdit *mLineEdit = nullptr;
};

#endif // SELECTIMAPWIDGET_H
