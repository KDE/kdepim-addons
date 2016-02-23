/*
  Copyright (c) 2016 Montel Laurent <montel@kde.org>

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License, version 2, as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef ADBLOCKPLUGINURLINTERCEPTOR_H
#define ADBLOCKPLUGINURLINTERCEPTOR_H

#include <MessageViewer/NetworkPluginUrlInterceptor>
#include <QVariant>
namespace MessageViewer
{
class NetworkPluginUrlInterceptorInterface;
class NetworkPluginUrlInterceptorConfigureWidget;
}
class AdblockPluginUrlInterceptor : public MessageViewer::NetworkPluginUrlInterceptor
{
    Q_OBJECT
public:
    explicit AdblockPluginUrlInterceptor(QObject *parent = Q_NULLPTR, const QList<QVariant> & = QList<QVariant>());
    ~AdblockPluginUrlInterceptor();

    MessageViewer::NetworkPluginUrlInterceptorInterface *createInterface(QObject *parent) Q_DECL_OVERRIDE;

    bool hasConfigureSupport() const Q_DECL_OVERRIDE;
    MessageViewer::NetworkPluginUrlInterceptorConfigureWidget *createConfigureWidget(QWidget *parent) Q_DECL_OVERRIDE;
};

#endif // ADBLOCKPLUGINURLINTERCEPTOR_H
