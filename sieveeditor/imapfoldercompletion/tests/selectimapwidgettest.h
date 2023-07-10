/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KSieveUi/AbstractMoveImapFolderWidget>
#include <QWidget>

class DefaultMoveImapFolderWidget : public KSieveUi::AbstractMoveImapFolderWidget
{
public:
    explicit DefaultMoveImapFolderWidget(QWidget *parent = nullptr);

    void setText(const QString &str) override;
    QString text() const override;
    void setSieveImapAccountSettings(const KSieveCore::SieveImapAccountSettings &account) override;
};

class SelectImapWidgetTest : public QWidget
{
    Q_OBJECT
public:
    explicit SelectImapWidgetTest(QWidget *parent = nullptr);
    ~SelectImapWidgetTest() override;
};
