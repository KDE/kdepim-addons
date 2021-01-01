/*
  SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-only
*/

#ifndef CSVWIDGET_H
#define CSVWIDGET_H

#include <QWidget>

class KUrlRequester;
class QUrl;
namespace MailMerge {
class CsvWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CsvWidget(QWidget *parent = nullptr);
    ~CsvWidget() override;

    void setPath(const QUrl &path);
    QUrl path() const;

private:
    KUrlRequester *mCvsUrlRequester = nullptr;
};
}

#endif // CSVWIDGET_H
