/*
   SPDX-FileCopyrightText: 2015-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef ENTERPRISEHEADERSTYLEPLUGIN_H
#define ENTERPRISEHEADERSTYLEPLUGIN_H

#include <MessageViewer/HeaderStylePlugin>

#include <QVariant>

namespace MessageViewer {
class EnterpriseHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit EnterpriseHeaderStylePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~EnterpriseHeaderStylePlugin() override;

    HeaderStyle *headerStyle() const override;
    HeaderStrategy *headerStrategy() const override;
    HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    QString name() const override;
    bool hasMargin() const override;
    QString alignment() const override;
    int elidedTextSize() const override;
private:
    HeaderStyle *mHeaderStyle = nullptr;
    HeaderStrategy *mHeaderStrategy = nullptr;
};
}
#endif // ENTERPRISEHEADERSTYLEPLUGIN_H
