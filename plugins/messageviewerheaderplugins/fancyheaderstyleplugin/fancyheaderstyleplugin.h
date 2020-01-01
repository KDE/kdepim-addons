/*
   Copyright (C) 2015-2020 Laurent Montel <montel@kde.org>

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

#ifndef FANCYHEADERSTYLEPLUGIN_H
#define FANCYHEADERSTYLEPLUGIN_H

#include "messageviewer/headerstyleplugin.h"

#include <QVariant>

namespace MessageViewer {
class FancyHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit FancyHeaderStylePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~FancyHeaderStylePlugin() override;

    HeaderStyle *headerStyle() const override;
    HeaderStrategy *headerStrategy() const override;
    HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    QString name() const override;
    int elidedTextSize() const override;
    QString extraScreenCss(const QString &headerFont) const override;
    QString extraPrintCss(const QString &headerFont) const override;
    QString extraCommonCss(const QString &headerFont) const override;
    QString attachmentHtml() const override;

private:
    HeaderStyle *mHeaderStyle = nullptr;
    HeaderStrategy *mHeaderStrategy = nullptr;
};
}
#endif // FANCYHEADERSTYLEPLUGIN_H
