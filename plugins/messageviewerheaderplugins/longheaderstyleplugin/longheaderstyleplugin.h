/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LONGHEADERSTYLEPLUGIN_H
#define LONGHEADERSTYLEPLUGIN_H

#include <MessageViewer/HeaderStylePlugin>

#include <QVariant>

namespace MessageViewer {
class LongHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit LongHeaderStylePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~LongHeaderStylePlugin() override;

    HeaderStyle *headerStyle() const override;
    HeaderStrategy *headerStrategy() const override;
    HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    QString name() const override;
private:
    HeaderStyle *const mHeaderStyle;
    HeaderStrategy *const mHeaderStrategy;
};
}
#endif // LONGHEADERSTYLEPLUGIN_H
