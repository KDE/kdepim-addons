/*
   SPDX-FileCopyrightText: 2015-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef STANDARDSHEADERSTYLEPLUGIN_H
#define STANDARDSHEADERSTYLEPLUGIN_H

#include <MessageViewer/HeaderStylePlugin>

#include <QVariant>

namespace MessageViewer {
class StandardsHeaderStylePlugin : public MessageViewer::HeaderStylePlugin
{
    Q_OBJECT
public:
    explicit StandardsHeaderStylePlugin(QObject *parent = nullptr, const QList<QVariant> & = QList<QVariant>());
    ~StandardsHeaderStylePlugin() override;

    HeaderStyle *headerStyle() const override;
    HeaderStrategy *headerStrategy() const override;
    HeaderStyleInterface *createView(KActionMenu *menu, QActionGroup *actionGroup, KActionCollection *ac, QObject *parent = nullptr) override;
    QString name() const override;
private:
    HeaderStyle *const mHeaderStyle;
    HeaderStrategy *const mHeaderStrategy;
};
}
#endif // STANDARDSHEADERSTYLEPLUGIN_H
