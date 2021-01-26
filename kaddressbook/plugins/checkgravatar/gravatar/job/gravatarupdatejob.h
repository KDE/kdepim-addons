/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRAVATARUPDATEJOB_H
#define GRAVATARUPDATEJOB_H

#include <AkonadiCore/Item>
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
    bool canStart() const;

    QString email() const;
    void setEmail(const QString &email);

    Akonadi::Item item() const;
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

#endif // GRAVATARUPDATEJOB_H
