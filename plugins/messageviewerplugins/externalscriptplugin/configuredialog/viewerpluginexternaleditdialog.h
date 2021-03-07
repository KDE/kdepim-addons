/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALEDITDIALOG_H
#define VIEWERPLUGINEXTERNALEDITDIALOG_H

#include <QDialog>

#include "../viewerpluginexternalscriptinfo.h"

class ViewerPluginExternalEditWidget;
class QPushButton;
class ViewerPluginExternalEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ViewerPluginExternalEditDialog(QWidget *parent = nullptr);
    ~ViewerPluginExternalEditDialog() override;

    void setScriptInfo(const ViewerPluginExternalScriptInfo &info);
    ViewerPluginExternalScriptInfo scriptInfo() const;

    void setExistingsNames(const QStringList &existingsNames);

private:
    void readConfig();
    void saveConfig();
    void slotScriptIsValid(bool valid);
    void slotAccepted();
    ViewerPluginExternalEditWidget *mEditWidget = nullptr;
    QPushButton *mOkButton = nullptr;
};

#endif // VIEWERPLUGINEXTERNALEDITDIALOG_H
