/*
    This file is part of Contact Editor.

    Copyright (C) 2016-2017 Laurent Montel <montel@kde.org>

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Library General Public License as published by
    the Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
    License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301, USA.
*/

#ifndef ADDRESSESLOCATIONENGINEPAGE_H
#define ADDRESSESLOCATIONENGINEPAGE_H

#include <QWebEnginePage>

class AddressesLocationEnginePage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit AddressesLocationEnginePage(QObject *parent = nullptr);
    ~AddressesLocationEnginePage();

Q_SIGNALS:
    void urlClicked(const QUrl &url);

protected:
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame) override;
};

#endif // ADDRESSESLOCATIONENGINEPAGE_H
