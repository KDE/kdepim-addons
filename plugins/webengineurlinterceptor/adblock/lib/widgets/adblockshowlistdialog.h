/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ADBLOCKSHOWLISTDIALOG_H
#define ADBLOCKSHOWLISTDIALOG_H

#include <QDialog>
#include <KSyntaxHighlighting/Repository>

class KJob;
class QTemporaryFile;

namespace KPIM {
class ProgressIndicatorLabel;
}

namespace KPIMTextEdit {
class PlainTextEditorWidget;
}
class QPushButton;
namespace AdBlock {
class AdBlockShowListDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AdBlockShowListDialog(bool showDeleteBrokenList, QWidget *parent = nullptr);
    ~AdBlockShowListDialog();

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

#endif // ADBLOCKSHOWLISTDIALOG_H
