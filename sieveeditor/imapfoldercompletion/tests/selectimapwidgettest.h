/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPWIDGETTEST_H
#define SELECTIMAPWIDGETTEST_H

#include <KSieveUi/AbstractMoveImapFolderWidget>
#include <QWidget>

class DefaultMoveImapFolderWidget : public KSieveUi::AbstractMoveImapFolderWidget
{
public:
    explicit DefaultMoveImapFolderWidget(QWidget *parent = nullptr);

    void setText(const QString &str) override;
    QString text() const override;
    void setSieveImapAccountSettings(const KSieveUi::SieveImapAccountSettings &account) override;
};

class SelectImapWidgetTest : public QWidget
{
    Q_OBJECT
public:
    explicit SelectImapWidgetTest(QWidget *parent = nullptr);
    ~SelectImapWidgetTest();
};

#endif // SELECTIMAPWIDGETTEST_H
