/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "autogenerateconfigureaskitem.h"
#include "pimautogeneratetext_export.h"
#include <QObject>

class PIMAUTOGENERATETEXT_EXPORT AutogenerateConfigureAskManager : public QObject
{
    Q_OBJECT
public:
    explicit AutogenerateConfigureAskManager(QObject *parent = nullptr);
    ~AutogenerateConfigureAskManager() override;

    void load();
    void save();

    [[nodiscard]] QList<AutogenerateConfigureAskItem> items() const;
    void setItems(const QList<AutogenerateConfigureAskItem> &newItems);

Q_SIGNALS:
    void changed();

private:
    QList<AutogenerateConfigureAskItem> mItems;
};
