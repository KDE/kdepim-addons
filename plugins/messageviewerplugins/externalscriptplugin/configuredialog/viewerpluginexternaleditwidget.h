/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALEDITWIDGET_H
#define VIEWERPLUGINEXTERNALEDITWIDGET_H

#include <QWidget>
#include "../viewerpluginexternalscriptinfo.h"
class QLineEdit;
class KUrlRequester;
class ViewerPluginExternalEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalEditWidget(QWidget *parent = nullptr);
    ~ViewerPluginExternalEditWidget();

    void setScriptInfo(const ViewerPluginExternalScriptInfo &info);
    ViewerPluginExternalScriptInfo scriptInfo() const;

    void save();
    void setExistingsNames(const QStringList &existingsNames);

Q_SIGNALS:
    void scriptIsValid(bool valid);

private:
    void slotInfoChanged();
    ViewerPluginExternalScriptInfo mScriptInfo;
    QStringList mExistingsNames;
    QLineEdit *mName = nullptr;
    QLineEdit *mDescription = nullptr;
    QLineEdit *mCommandLine = nullptr;
    KUrlRequester *mExecutable = nullptr;
};

#endif // VIEWERPLUGINEXTERNALEDITWIDGET_H
