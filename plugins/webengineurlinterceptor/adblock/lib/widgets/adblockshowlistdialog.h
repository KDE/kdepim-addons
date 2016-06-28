/*
   Copyright (C) 2013-2016 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef ADBLOCKSHOWLISTDIALOG_H
#define ADBLOCKSHOWLISTDIALOG_H

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
    explicit AdBlockShowListDialog(bool showDeleteBrokenList, QWidget *parent = Q_NULLPTR);
    ~AdBlockShowListDialog();

    void setAdBlockListPath(const QString &localPath, const QString &url);

    void setListName(const QString &listName);
private Q_SLOTS:
    void slotFinished(KJob *job);
    void slotDeleteBrokenList();

Q_SIGNALS:
    void deleteList(const QString &name);

private:
    void readConfig();
    void writeConfig();
    void downLoadList(const QString &url);

    QString mListName;
    KPIMTextEdit::PlainTextEditorWidget *mTextEdit;
    QTemporaryFile *mTemporaryFile;
    KPIM::ProgressIndicatorLabel *mProgress;
    QPushButton *mUser1Button;
};
}

#endif // ADBLOCKSHOWLISTDIALOG_H
