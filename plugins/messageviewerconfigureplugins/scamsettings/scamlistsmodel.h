/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

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
    enum ScamRole {
        Enabled,
        Domain,
        Check,
        LastColumn = Check,
    };
    Q_ENUM(ScamRole)

    explicit ScamListsModel(QObject *parent = nullptr);
    ~ScamListsModel() override;

    [[nodiscard]] QList<MessageViewer::ScamDetectionInfo> info() const;
    void setInfo(const QList<MessageViewer::ScamDetectionInfo> &newInfo);

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    [[nodiscard]] bool insertInfo(const MessageViewer::ScamDetectionInfo &info);
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

private:
    QList<MessageViewer::ScamDetectionInfo> mInfo;
};
