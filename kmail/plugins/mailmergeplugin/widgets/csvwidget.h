/*
  SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#pragma once

#include "mailmergeplugin_private_export.h"
#include <QWidget>
class KUrlRequester;
class QUrl;
namespace MailMerge
{
class MAILMERGEPRIVATE_TESTS_EXPORT CsvWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CsvWidget(QWidget *parent = nullptr);
    ~CsvWidget() override;

    void setPath(const QUrl &path);
    [[nodiscard]] QUrl path() const;

private:
    KUrlRequester *const mCvsUrlRequester;
};
}
