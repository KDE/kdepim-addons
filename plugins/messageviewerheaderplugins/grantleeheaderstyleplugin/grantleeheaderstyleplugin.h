/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef GRANTLEEHEADERSTYLEPLUGIN_H
#define GRANTLEEHEADERSTYLEPLUGIN_H

#include <MessageViewer/HeaderStylePlugin>

#include <QVariant>

namespace MessageViewer {
class GrantleeHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit GrantleeHeaderStylePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~GrantleeHeaderStylePlugin() override;

    HeaderStyle *headerStyle() const override;
    HeaderStrategy *headerStrategy() const override;
    HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    QString name() const override;
private:
    HeaderStyle *const mHeaderStyle;
    HeaderStrategy *const mHeaderStrategy;
};
}
#endif // GRANTLEEHEADERSTYLEPLUGIN_H
