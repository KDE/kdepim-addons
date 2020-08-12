/*
  SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef SELECTATTACHMENTDIALOG_H
#define SELECTATTACHMENTDIALOG_H

#include <QDialog>
class KUrlRequester;

namespace MailMerge {
class SelectAttachmentDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SelectAttachmentDialog(QWidget *parent = nullptr);
    ~SelectAttachmentDialog();

    void setAttachmentPath(const QString &path);
    QString attachmentPath() const;

private:
    KUrlRequester *mUrlRequester = nullptr;
};
}

#endif // SELECTATTACHMENTDIALOG_H
