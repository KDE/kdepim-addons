/*
   Copyright (C) 2015-2019 Montel Laurent <montel@kde.org>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef SENDVCARDSJOB_H
#define SENDVCARDSJOB_H
#include <QObject>
#include <AkonadiCore/Item>
#include <QStringList>
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
    ~SendVcardsJob();

    bool start();

    KContacts::VCardConverter::Version version() const;
    void setVersion(KContacts::VCardConverter::Version version);

Q_SIGNALS:
    void sendVCardsError(const QString &error);

private:
    void slotExpandGroupResult(KJob *job);
    void createTemporaryFile(const QByteArray &data, const QString &filename);
    void createTemporaryDir();
    void jobFinished();
    Akonadi::Item::List mListItem;
    MimeTreeParser::AttachmentTemporaryFilesDirs *mAttachmentTemporary = nullptr;
    QTemporaryDir *mTempDir = nullptr;
    KContacts::VCardConverter::Version mVersion = KContacts::VCardConverter::v3_0;
    int mExpandGroupJobCount = 0;
};
}

#endif // SENDVCARDSJOB_H
