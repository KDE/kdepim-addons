/*
   SPDX-FileCopyrightText: 2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QAbstractListModel>
namespace MessageViewer
{
class ScamDetectionInfo;
}
class ScamListsModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ScamListsModel(QObject *parent = nullptr);
    ~ScamListsModel() override;

    [[nodiscard]] QList<MessageViewer::ScamDetectionInfo> info() const;
    void setInfo(const QList<MessageViewer::ScamDetectionInfo> &newInfo);

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    QList<MessageViewer::ScamDetectionInfo> mInfo;
};
