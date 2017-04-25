/*
   Copyright (C) 2015-2016 Montel Laurent <montel@kde.org>

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

#ifndef GRAVATARUPDATEWIDGET_H
#define GRAVATARUPDATEWIDGET_H

#include <QWidget>
#include <QUrl>
class QLabel;
class QPushButton;
class QCheckBox;

namespace Gravatar {
class GravatarResolvUrlJob;
}
namespace KABGravatar {
class GravatarUpdateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GravatarUpdateWidget(QWidget *parent = nullptr);
    ~GravatarUpdateWidget();

    void setEmail(const QString &email);
    QPixmap pixmap() const;
    void setOriginalPixmap(const QPixmap &pix);
    QUrl resolvedUrl() const;

    void setOriginalUrl(const QUrl &url);

Q_SIGNALS:
    void activateDialogButton(bool state);

private:
    void slotSearchGravatar();
    void slotSearchGravatarFinished(Gravatar::GravatarResolvUrlJob *job);
    void slotResolvUrl(const QUrl &url);

    QString mEmail;
    QPixmap mPixmap;
    QUrl mCurrentUrl;
    QLabel *mEmailLab;
    QPushButton *mSearchGravatar;
    QLabel *mResultGravatar;
    QCheckBox *mUseHttps;
    QCheckBox *mUseLibravatar;
    QCheckBox *mFallbackGravatar;
};
}

#endif // GRAVATARUPDATEWIDGET_H
