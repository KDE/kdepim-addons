/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

class QCheckBox;
class VCardExportSelectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VCardExportSelectionWidget(QWidget *parent = nullptr);
    ~VCardExportSelectionWidget() override;
    enum ExportField {
        None = 0,
        Private = 1,
        Business = 2,
        Other = 4,
        Encryption = 8,
        Picture = 16,
        DiplayName = 32,
    };
    Q_ENUMS(ExportField)
    Q_DECLARE_FLAGS(ExportFields, ExportField)

    ExportFields exportType() const;

private:
    void readSettings();
    void writeSettings();
    QCheckBox *mPrivateBox = nullptr;
    QCheckBox *mBusinessBox = nullptr;
    QCheckBox *mOtherBox = nullptr;
    QCheckBox *mEncryptionKeys = nullptr;
    QCheckBox *mPictureBox = nullptr;
    QCheckBox *mDisplayNameBox = nullptr;
};
