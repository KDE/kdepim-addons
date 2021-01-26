/*
  SPDX-FileCopyrightText: 2014-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef MAILMERGEWIDGET_H
#define MAILMERGEWIDGET_H

#include <QWidget>

class QComboBox;
class QStackedWidget;

namespace MailMerge
{
class CsvWidget;
class AttachmentListWidget;
class AddressBookWidget;
class MailMergeWidget : public QWidget
{
    Q_OBJECT
public:
    enum SourceType { AddressBook = 0, CSV = 1 };

    explicit MailMergeWidget(QWidget *parent = nullptr);
    ~MailMergeWidget() override;

Q_SIGNALS:
    void sourceModeChanged(MailMerge::MailMergeWidget::SourceType);

private Q_SLOTS:
    void slotSourceChanged(int index);

private:
    QComboBox *mSource = nullptr;
    QStackedWidget *mStackedWidget = nullptr;
    AttachmentListWidget *mAttachment = nullptr;
    MailMerge::CsvWidget *mCsvWidget = nullptr;
    MailMerge::AddressBookWidget *mAddressbookWidget = nullptr;
};
}
#endif // MAILMERGEWIDGET_H
