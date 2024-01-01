/*
   SPDX-FileCopyrightText: 2016-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "../viewerpluginexternalscriptinfo.h"
#include <QWidget>
class QLineEdit;
class KUrlRequester;
class ViewerPluginExternalEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalEditWidget(QWidget *parent = nullptr);
    ~ViewerPluginExternalEditWidget() override;

    void setScriptInfo(const ViewerPluginExternalScriptInfo &info);
    [[nodiscard]] ViewerPluginExternalScriptInfo scriptInfo() const;

    void save();
    void setExistingsNames(const QStringList &existingsNames);

Q_SIGNALS:
    void scriptIsValid(bool valid);

private:
    void slotLinkClicked(const QString &link);
    void slotInfoChanged();
    ViewerPluginExternalScriptInfo mScriptInfo;
    QStringList mExistingsNames;
    QString mCommandWhatsThis;
    QLineEdit *const mName;
    QLineEdit *const mDescription;
    QLineEdit *const mCommandLine;
    KUrlRequester *const mExecutable;
};
