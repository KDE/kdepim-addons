/*
   SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <Akonadi/Item>
#include <QObject>
#include <QUrl>
namespace Gravatar
{
class GravatarResolvUrlJob;
}
namespace KABGravatar
{
class GravatarUpdateJob : public QObject
{
    Q_OBJECT
public:
    explicit GravatarUpdateJob(QObject *parent = nullptr);
    ~GravatarUpdateJob() override;

    void start();
    Q_REQUIRED_RESULT bool canStart() const;

    Q_REQUIRED_RESULT QString email() const;
    void setEmail(const QString &email);

    Q_REQUIRED_RESULT Akonadi::Item item() const;
    void setItem(const Akonadi::Item &item);

Q_SIGNALS:
    void resolvedUrl(const QUrl &url);
    void gravatarPixmap(const QPixmap &pix);

private:
    void slotGravatarResolvUrlFinished(Gravatar::GravatarResolvUrlJob *job);
    void slotUpdateGravatarDone(KJob *job);
    void updatePixmap(const QPixmap &pix);
    QString mEmail;
    Akonadi::Item mItem;
};
}
