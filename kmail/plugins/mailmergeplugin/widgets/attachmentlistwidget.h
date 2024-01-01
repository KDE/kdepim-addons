/*
  SPDX-FileCopyrightText: 2014-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <PimCommon/SimpleStringListEditor>

namespace MailMerge
{
class AttachmentListWidget : public PimCommon::SimpleStringListEditor
{
    Q_OBJECT
public:
    explicit AttachmentListWidget(QWidget *parent = nullptr,
                                  ButtonCode buttons = Unsorted,
                                  const QString &addLabel = QString(),
                                  const QString &removeLabel = QString(),
                                  const QString &modifyLabel = QString());
    ~AttachmentListWidget() override;

    void addNewEntry() override;
    [[nodiscard]] QString modifyEntry(const QString &text) override;
};
}
