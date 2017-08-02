/*
   Copyright (c) 2015-2017 Montel Laurent <montel@kde.org>

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

#ifndef GRAVATARUPDATEDIALOG_H
#define GRAVATARUPDATEDIALOG_H

#include <QDialog>
namespace KABGravatar {
class GravatarUpdateWidget;
class GravatarUpdateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GravatarUpdateDialog(QWidget *parent = nullptr);
    ~GravatarUpdateDialog();

    void setEmail(const QString &email);

    QPixmap pixmap() const;
    void setOriginalPixmap(const QPixmap &pix);

    void setOriginalUrl(const QUrl &url);

    QUrl resolvedUrl() const;

    bool saveUrl() const;
private:
    void slotSaveImage();
    void slotSaveUrl();

    void slotActivateButton(bool state);
    void readConfig();
    void writeConfig();
    GravatarUpdateWidget *mGravatarUpdateWidget;
    QPushButton *mSaveImageButton;
    QPushButton *mSaveUrlButton;
    bool mSaveUrl;
};
}
#endif // GRAVATARUPDATEDIALOG_H
