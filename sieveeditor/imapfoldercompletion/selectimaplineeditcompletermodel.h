/*
   SPDX-FileCopyrightText: 2017-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef SELECTIMAPLINEEDITCOMPLETERMODEL_H
#define SELECTIMAPLINEEDITCOMPLETERMODEL_H

#include <QObject>
class KDescendantsProxyModel;
class QAbstractProxyModel;
namespace KSieveUi {
class SieveImapAccountSettings;
}
class SelectImapLineEditCompleterModel : public QObject
{
    Q_OBJECT
public:
    explicit SelectImapLineEditCompleterModel(const KSieveUi::SieveImapAccountSettings &account, QObject *parent = nullptr);
    ~SelectImapLineEditCompleterModel();

    Q_REQUIRED_RESULT QAbstractProxyModel *completerModel() const;
private:
    KDescendantsProxyModel *const mFlatProxy;
};

#endif // SELECTIMAPLINEEDITCOMPLETERMODEL_H
