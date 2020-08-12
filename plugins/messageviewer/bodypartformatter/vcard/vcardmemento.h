/*
   SPDX-FileCopyrightText: 2012-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VCARDMEMENTO_H
#define VCARDMEMENTO_H

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/Enums>

#include <QObject>
#include <KContacts/Addressee>

class KJob;

namespace MessageViewer {
struct VCard {
    VCard()
    {
    }

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
    int mIndex;
    bool mFinished;
};
}

#endif // VCARDMEMENTO_H
