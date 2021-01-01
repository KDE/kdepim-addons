/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SENDVCARDSJOB_H
#define SENDVCARDSJOB_H
#include <QObject>
#include <AkonadiCore/Item>
#include <KContacts/VCardConverter>

class QTemporaryDir;
namespace MimeTreeParser {
class AttachmentTemporaryFilesDirs;
}
namespace KABSendVCards {
class SendVcardsJob : public QObject
{
    Q_OBJECT
public:
    explicit SendVcardsJob(const Akonadi::Item::List &listItem, QObject *parent = nullptr);
    ~SendVcardsJob() override;

    Q_REQUIRED_RESULT bool start();

    KContacts::VCardConverter::Version version() const;
    void setVersion(KContacts::VCardConverter::Version version);

Q_SIGNALS:
    void sendVCardsError(const QString &error);

private:
    void slotExpandGroupResult(KJob *job);
    void createTemporaryFile(const QByteArray &data, const QString &filename);
    void createTemporaryDir();
    void jobFinished();
    const Akonadi::Item::List mListItem;
    MimeTreeParser::AttachmentTemporaryFilesDirs *mAttachmentTemporary = nullptr;
    QTemporaryDir *mTempDir = nullptr;
    KContacts::VCardConverter::Version mVersion = KContacts::VCardConverter::v3_0;
    int mExpandGroupJobCount = 0;
};
}

#endif // SENDVCARDSJOB_H
