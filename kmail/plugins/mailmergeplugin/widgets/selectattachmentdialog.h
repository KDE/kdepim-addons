/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef SELECTATTACHMENTDIALOG_H
#define SELECTATTACHMENTDIALOG_H

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
    Q_REQUIRED_RESULT QString attachmentPath() const;

private:
    KUrlRequester *mUrlRequester = nullptr;
};
}

#endif // SELECTATTACHMENTDIALOG_H
