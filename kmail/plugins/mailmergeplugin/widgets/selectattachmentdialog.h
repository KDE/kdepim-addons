/*
  SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include <QDialog>
class KUrlRequester;

namespace MailMerge
{
class SelectAttachmentDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectAttachmentDialog(QWidget *parent = nullptr);
    ~SelectAttachmentDialog() override;

    void setAttachmentPath(const QUrl &path);
    [[nodiscard]] QString attachmentPath() const;

private:
    KUrlRequester *const mUrlRequester;
};
}
