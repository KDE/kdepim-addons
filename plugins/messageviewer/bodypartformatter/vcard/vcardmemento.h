/*
   SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/Enums>

#include <KContacts/Addressee>
#include <QObject>

class KJob;

namespace MessageViewer
{
struct VCard {
    VCard() = default;

    VCard(const QString &str, bool b)
        : email(str)
        , found(b)
    {
    }

    KContacts::Addressee address;
    QString email;
    bool found = false;
};

class VcardMemento : public QObject, public MimeTreeParser::Interface::BodyPartMemento
{
    Q_OBJECT
public:
    explicit VcardMemento(const QStringList &emails);
    ~VcardMemento() override;

    bool finished() const;

    void detach() override;

    bool vcardExist(int index) const;

    KContacts::Addressee address(int index) const;

Q_SIGNALS:
    // TODO: Factor our update and detach into base class
    void update(MimeTreeParser::UpdateMode);

private:
    void slotSearchJobFinished(KJob *job);
    void checkEmail();
    void continueToCheckEmail();
    QVector<VCard> mVCardList;
    int mIndex = 0;
    bool mFinished = false;
};
}
