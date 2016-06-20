/*
   Copyright (C) 2012-2016 Montel Laurent <montel@kde.org>

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

#ifndef VCARDMEMENTO_H
#define VCARDMEMENTO_H

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/Enums>

#include <QObject>
#include <QMap>
#include <KContacts/Addressee>

class KJob;

namespace MessageViewer
{

struct VCard {
    VCard()
        : found(false)
    {

    }

    VCard(const QString &str, bool b)
        : email(str), found(b)
    {
    }
    KContacts::Addressee address;
    QString email;
    bool found;
};

class VcardMemento : public QObject, public MimeTreeParser::Interface::BodyPartMemento
{
    Q_OBJECT
public:
    explicit VcardMemento(const QStringList &emails);
    ~VcardMemento();

    bool finished() const;

    void detach() Q_DECL_OVERRIDE;

    bool vcardExist(int index) const;

    KContacts::Addressee address(int index) const;

private Q_SLOTS:
    void slotSearchJobFinished(KJob *job);

Q_SIGNALS:
    // TODO: Factor our update and detach into base class
    void update(MimeTreeParser::UpdateMode);

private:
    void checkEmail();
    void continueToCheckEmail();
    QVector<VCard> mVCardList;
    int mIndex;
    bool mFinished;
};
}

#endif // VCARDMEMENTO_H
