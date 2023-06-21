/*
  SPDX-FileCopyrightText: 2014-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#include "attachmentlistwidget.h"
#include "selectattachmentdialog.h"

#include <QPointer>
#include <QPushButton>
#include <QUrl>

using namespace MailMerge;
AttachmentListWidget::AttachmentListWidget(QWidget *parent, ButtonCode buttons, const QString &addLabel, const QString &removeLabel, const QString &modifyLabel)
    : PimCommon::SimpleStringListEditor(parent, buttons, addLabel, removeLabel, modifyLabel, QString())
{
}

AttachmentListWidget::~AttachmentListWidget() = default;

void AttachmentListWidget::addNewEntry()
{
    QPointer<SelectAttachmentDialog> dlg = new SelectAttachmentDialog(this);
    if (dlg->exec()) {
        insertNewEntry(dlg->attachmentPath());
    }
    delete dlg;
}

QString AttachmentListWidget::modifyEntry(const QString &text)
{
    QString attachmentPath;
    QPointer<SelectAttachmentDialog> dlg = new SelectAttachmentDialog(this);
    dlg->setAttachmentPath(QUrl::fromLocalFile(text));
    if (dlg->exec()) {
        attachmentPath = dlg->attachmentPath();
    }
    delete dlg;
    return attachmentPath;
}

#include "moc_attachmentlistwidget.cpp"
