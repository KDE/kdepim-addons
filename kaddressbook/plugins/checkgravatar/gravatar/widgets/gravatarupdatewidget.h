/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QUrl>
#include <QWidget>
class QLabel;
class QPushButton;

namespace Gravatar
{
class GravatarResolvUrlJob;
}
namespace KABGravatar
{
class GravatarUpdateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GravatarUpdateWidget(QWidget *parent = nullptr);
    ~GravatarUpdateWidget() override;

    void setEmail(const QString &email);
    Q_REQUIRED_RESULT QPixmap pixmap() const;
    void setOriginalPixmap(const QPixmap &pix);
    Q_REQUIRED_RESULT QUrl resolvedUrl() const;

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
    QLabel *const mEmailLab;
    QPushButton *const mSearchGravatar;
    QLabel *const mResultGravatar;
};
}
