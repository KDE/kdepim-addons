/* SPDX-FileCopyrightText: 2010 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.net>
   SPDX-FileContributor: Sérgio Martins <sergio.martins@kdab.com>

   SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/
#ifndef MEMORYCALENDARMEMENTO_H
#define MEMORYCALENDARMEMENTO_H

#include <MimeTreeParser/BodyPart>
#include <MimeTreeParser/Enums>

#include <Akonadi/Calendar/CalendarBase>
#include <QObject>

namespace MessageViewer
{
class MemoryCalendarMemento : public QObject, public MimeTreeParser::Interface::BodyPartMemento
{
    Q_OBJECT
public:
    MemoryCalendarMemento();

    bool finished() const;
    Akonadi::CalendarBase::Ptr calendar() const;

    void detach() override;

Q_SIGNALS:
    // TODO: Factor our update and detach into base class
    void update(MimeTreeParser::UpdateMode);

private Q_SLOTS:
    void finalize();

private:
    void slotCalendarLoaded(bool success, const QString &errorMessage);
    bool mFinished = false;
    Akonadi::CalendarBase::Ptr mCalendar;
};
}

#endif
