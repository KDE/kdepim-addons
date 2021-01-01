/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
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
    ~GravatarUpdateDialog() override;

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
    GravatarUpdateWidget *mGravatarUpdateWidget = nullptr;
    QPushButton *mSaveImageButton = nullptr;
    QPushButton *mSaveUrlButton = nullptr;
    bool mSaveUrl = false;
};
}
#endif // GRAVATARUPDATEDIALOG_H
