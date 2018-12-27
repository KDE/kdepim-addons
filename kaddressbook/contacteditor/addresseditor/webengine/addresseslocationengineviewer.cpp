/*
    This file is part of Contact Editor.

    Copyright (C) 2016-2019 Laurent Montel <montel@kde.org>

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

#include "addresseslocationengineviewer.h"
#include "addresseslocationenginepage.h"
#include "addresslocationeditorplugin_debug.h"
#include "../addresseslocationgrantleeformater.h"
#include <KMessageBox>
#include <KLocalizedString>
#include <QUrlQuery>

AddressesLocationEngineViewer::AddressesLocationEngineViewer(QWidget *parent)
    : QWebEngineView(parent)
    , mAddressesLocationGrantleeFormatter(new AddressesLocationGrantleeFormater(this))
{
    AddressesLocationEnginePage *pageEngine = new AddressesLocationEnginePage(this);
    setPage(pageEngine);

    setFocusPolicy(Qt::WheelFocus);
    connect(pageEngine, &AddressesLocationEnginePage::urlClicked, this, &AddressesLocationEngineViewer::slotLinkClicked);

    setContextMenuPolicy(Qt::CustomContextMenu);
}

AddressesLocationEngineViewer::~AddressesLocationEngineViewer()
{
}

void AddressesLocationEngineViewer::setReadOnly(bool readOnly)
{
    mAddressesLocationGrantleeFormatter->setReadOnly(readOnly);
    updateView();
}

void AddressesLocationEngineViewer::slotLinkClicked(const QUrl &url)
{
    if (url.scheme() == QLatin1String("addresslocationaction")) {
        const QString urlPath(url.path());
        if (url.hasQuery()) {
            const QUrlQuery urlQuery(url);
            const int addressId = urlQuery.queryItemValue(QStringLiteral("id")).toInt();
            if (urlPath == QStringLiteral("removeaddress")) {
                if (!mEditMode) {
                    removeAddress(addressId);
                }
            } else if (urlPath == QStringLiteral("editaddress")) {
                if (!mEditMode) {
                    editAddress(addressId);
                }
            } else {
                qCDebug(ADDRESSLOCATIONEDITORPLUGIN_LOG) << "Unknown url" << url;
            }
        }
    }
}

void AddressesLocationEngineViewer::removeAddress(int index)
{
    if (index < 0) {
        return;
    } else if (index < mAddresses.count()) {
        const int result = KMessageBox::questionYesNo(this, i18n("Do you really want to delete this address?"));

        if (result != KMessageBox::Yes) {
            return;
        }
        mAddresses.remove(index);
        updateView();
    }
}

void AddressesLocationEngineViewer::editAddress(int index)
{
    if (index < 0) {
        return;
    } else if (index < mAddresses.count()) {
        mEditMode = true;
        Q_EMIT modifyAddress(mAddresses.at(index), index);
    }
}

void AddressesLocationEngineViewer::replaceAddress(const KContacts::Address &address, int index)
{
    if (index < 0) {
        return;
    } else if (index < mAddresses.count()) {
        mAddresses[index] = address;
        updateView();
    }
    mEditMode = false;
}

void AddressesLocationEngineViewer::updateAddressCanceled()
{
    mEditMode = false;
}

void AddressesLocationEngineViewer::updateView()
{
    const QString html = mAddressesLocationGrantleeFormatter->formatAddresses(mAddresses);
    setHtml(html, QUrl(QStringLiteral("file://")));
}

void AddressesLocationEngineViewer::addAddress(const KContacts::Address &address)
{
    if (!address.isEmpty()) {
        mAddresses.append(address);
        updateView();
    }
}

KContacts::Address::List AddressesLocationEngineViewer::addresses() const
{
    return mAddresses;
}

void AddressesLocationEngineViewer::setAddresses(const KContacts::Address::List &addresses)
{
    mAddresses = addresses;
    updateView();
}
