/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "common/tooljobbase.h"
#include <Akonadi/Collection>
#include <QStringList>

class CreateMailToolJob : public ToolJobBase
{
    Q_OBJECT
public:
    explicit CreateMailToolJob(QObject *parent = nullptr);
    ~CreateMailToolJob() override;

    void setSubject(const QString &subject);

    void setTo(const QStringList &to);

    void setCc(const QStringList &cc);

    void setBcc(const QStringList &bcc);

    void setBody(const QString &body);

    [[nodiscard]] bool canStart() const override;

protected:
    void startJob() override;
    [[nodiscard]] QString invalidArgumentsMessage() const override;

private:
    void slotDraftsCollectionResult(KJob *job);
    void slotItemCreateResult(KJob *job);
    void createMail(const Akonadi::Collection &collection);
    QString mSubject;
    QStringList mTo;
    QStringList mCc;
    QStringList mBcc;
    QString mBody;
};
