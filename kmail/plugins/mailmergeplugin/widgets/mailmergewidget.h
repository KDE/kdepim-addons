/*
  SPDX-FileCopyrightText: 2014-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include "mailmergeplugin_private_export.h"
#include <QWidget>
class QComboBox;
class QStackedWidget;

namespace MailMerge
{
class CsvWidget;
class AttachmentListWidget;
class AddressBookWidget;
class MAILMERGEPRIVATE_TESTS_EXPORT MailMergeWidget : public QWidget
{
    Q_OBJECT
public:
    enum SourceType {
        AddressBook = 0,
        CSV = 1,
    };

    explicit MailMergeWidget(QWidget *parent = nullptr);
    ~MailMergeWidget() override;

Q_SIGNALS:
    void sourceModeChanged(MailMerge::MailMergeWidget::SourceType);

private Q_SLOTS:
    void slotSourceChanged(int index);

private:
    QComboBox *const mSource;
    QStackedWidget *const mStackedWidget;
    AttachmentListWidget *mAttachment = nullptr;
    MailMerge::CsvWidget *const mCsvWidget;
    MailMerge::AddressBookWidget *const mAddressbookWidget;
};
}
