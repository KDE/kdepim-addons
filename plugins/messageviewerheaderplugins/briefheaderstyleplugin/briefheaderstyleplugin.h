/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef BRIEFHEADERSTYLEPLUGIN_H
#define BRIEFHEADERSTYLEPLUGIN_H

#include <MessageViewer/HeaderStylePlugin>

#include <QVariant>

namespace MessageViewer {
class HeaderStyleInterface;
class BriefHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit BriefHeaderStylePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~BriefHeaderStylePlugin() override;

    HeaderStyle *headerStyle() const override;
    HeaderStrategy *headerStrategy() const override;
    HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    QString name() const override;
private:
    HeaderStyle *mHeaderStyle = nullptr;
    HeaderStrategy *mHeaderStrategy = nullptr;
};
}
#endif // BRIEFHEADERSTYLEPLUGIN_H
