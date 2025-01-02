/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
namespace KABGravatar
{
class GravatarUpdateWidget;
class GravatarUpdateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit GravatarUpdateDialog(QWidget *parent = nullptr);
    ~GravatarUpdateDialog() override;

    void setEmail(const QString &email);

    [[nodiscard]] QPixmap pixmap() const;
    void setOriginalPixmap(const QPixmap &pix);

    void setOriginalUrl(const QUrl &url);

    [[nodiscard]] QUrl resolvedUrl() const;

    [[nodiscard]] bool saveUrl() const;

private:
    void slotSaveImage();
    void slotSaveUrl();

    void slotActivateButton(bool state);
    void readConfig();
    void writeConfig();
    GravatarUpdateWidget *const mGravatarUpdateWidget;
    QPushButton *const mSaveImageButton;
    QPushButton *const mSaveUrlButton;
    bool mSaveUrl = false;
};
}
