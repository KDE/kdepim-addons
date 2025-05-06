/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "autogenerateconfigureaskinfo.h"
#include "pimautogeneratetext_export.h"
#include <KSharedConfig>
#include <QObject>

class PIMAUTOGENERATETEXT_EXPORT AutogenerateConfigureAskManager : public QObject
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskManager(QObject *parent = nullptr);
    ~AutogenerateConfigureAskManager() override;

    void load();
    void save();

    [[nodiscard]] QList<AutogenerateConfigureAskInfo> items() const;
    void setItems(const QList<AutogenerateConfigureAskInfo> &newItems);

Q_SIGNALS:
    void changed();

private:
    [[nodiscard]] QStringList keyRecorderList(KSharedConfig::Ptr &config) const;
    QList<AutogenerateConfigureAskInfo> mItems;
};
