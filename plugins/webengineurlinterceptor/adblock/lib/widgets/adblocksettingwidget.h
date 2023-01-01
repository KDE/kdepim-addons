/* ============================================================
 *
 * This file is a part of the rekonq project
 * SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>
 * based on code from rekonq
 * SPDX-FileCopyrightText: 2010-2012 Andrea Diamantini <adjam7 at gmail dot com>
 *
 *
 * SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
 *
 * ============================================================ */

#pragma once

#include "adblocklib_export.h"

// Qt Includes
#include <QListWidgetItem>
#include <QWidget>

namespace Ui
{
class adblock;
}

namespace AdBlock
{
class AdBlockSubscription;
class AdBlockListwidgetItem : public QListWidgetItem
{
public:
    explicit AdBlockListwidgetItem(QListWidget *parent);
    AdBlockSubscription *subscription() const;
    void setSubscription(AdBlockSubscription *subscription);

private:
    AdBlockSubscription *mSubscription = nullptr;
};

class ADBLOCKLIB_EXPORT AdBlockSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdBlockSettingWidget(QWidget *parent = nullptr);
    ~AdBlockSettingWidget() override;

    bool changed() const;

    void save();
    void doLoadFromGlobalSettings();
    void doResetToDefaultsOther();

Q_SIGNALS:
    void changed(bool);
    void settingsChanged();

protected:
    bool event(QEvent *event) override;

private:
    void hasChanged();
    void slotInfoLinkActivated(const QString &);
    void insertRule();
    void removeRule();
    void slotAddFilter();
    void slotRemoveSubscription();
    void slotUpdateButtons();
    void slotShowList();
    void slotImportFilters();
    void slotExportFilters();
    void slotEditFilter();
    void slotManualFilterLineEditTextChanged(const QString &);
    void slotAutomaticFilterDouble(QListWidgetItem *item);
    void slotDeleteList(const QString &listName);
    void updateCheckBox();
    void addManualFilter(const QString &text, const QStringList &excludeRules = QStringList());
    void showAutomaticFilterList(QListWidgetItem *item);
    void slotManualFiltersChanged(QListWidgetItem *item);
    void slotSelectionChanged();
    enum List {
        UrlList = Qt::UserRole + 1,
        PathList = Qt::UserRole + 2,
    };
    AdBlockSubscription *mCustomSubscription = nullptr;
    Ui::adblock *mUi = nullptr;
    bool mChanged = false;
    bool mBlockUpdate = true;
};
}
