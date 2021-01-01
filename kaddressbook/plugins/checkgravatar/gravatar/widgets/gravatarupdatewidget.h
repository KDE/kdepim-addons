/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAVATARUPDATEWIDGET_H
#define GRAVATARUPDATEWIDGET_H

#include <QWidget>
#include <QUrl>
class QLabel;
class QPushButton;

namespace Gravatar {
class GravatarResolvUrlJob;
}
namespace KABGravatar {
class GravatarUpdateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GravatarUpdateWidget(QWidget *parent = nullptr);
    ~GravatarUpdateWidget() override;

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
    QLabel *mEmailLab = nullptr;
    QPushButton *mSearchGravatar = nullptr;
    QLabel *mResultGravatar = nullptr;
};
}

#endif // GRAVATARUPDATEWIDGET_H
