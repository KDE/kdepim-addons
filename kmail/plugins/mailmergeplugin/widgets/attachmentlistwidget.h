/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef ATTACHMENTLISTWIDGET_H
#define ATTACHMENTLISTWIDGET_H

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
    Q_REQUIRED_RESULT QString modifyEntry(const QString &text) override;
};
}
#endif // ATTACHMENTLISTWIDGET_H
