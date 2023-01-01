/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KSyntaxHighlighting/Repository>
#include <QDialog>

class KJob;
class QTemporaryFile;

namespace KPIM
{
class ProgressIndicatorLabel;
}

namespace KPIMTextEdit
{
class PlainTextEditorWidget;
}
class QPushButton;
namespace AdBlock
{
class AdBlockShowListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdBlockShowListDialog(bool showDeleteBrokenList, QWidget *parent = nullptr);
    ~AdBlockShowListDialog() override;

    void setAdBlockListPath(const QString &localPath, const QString &url);

    void setListName(const QString &listName);
Q_SIGNALS:
    void deleteList(const QString &name);

private:
    void slotFinished(KJob *job);
    void slotDeleteBrokenList();
    void readConfig();
    void writeConfig();
    void downLoadList(const QString &url);

    QString mListName;
    KPIMTextEdit::PlainTextEditorWidget *mTextEdit = nullptr;
    QTemporaryFile *mTemporaryFile = nullptr;
    KPIM::ProgressIndicatorLabel *mProgress = nullptr;
    QPushButton *mUser1Button = nullptr;
    KSyntaxHighlighting::Repository mSyntaxRepo;
};
}
