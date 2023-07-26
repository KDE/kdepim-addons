/*
   SPDX-FileCopyrightText: 2016-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>
#include <QString>
class ViewerPluginExternalScriptInfo
{
public:
    ViewerPluginExternalScriptInfo();
    Q_REQUIRED_RESULT QString name() const;
    void setName(const QString &name);

    Q_REQUIRED_RESULT QString commandLine() const;
    void setCommandLine(const QString &commandLine);

    Q_REQUIRED_RESULT QString executable() const;
    void setExecutable(const QString &executable);

    Q_REQUIRED_RESULT QString description() const;
    void setDescription(const QString &description);

    Q_REQUIRED_RESULT QString icon() const;
    void setIcon(const QString &icon);

    Q_REQUIRED_RESULT bool isValid() const;

    Q_REQUIRED_RESULT bool isReadOnly() const;
    void setIsReadOnly(bool isReadOnly);

    Q_REQUIRED_RESULT QString fileName() const;
    void setFileName(const QString &fileName);

    Q_REQUIRED_RESULT bool operator==(const ViewerPluginExternalScriptInfo &other) const;

private:
    QString mCommandLine;
    QString mName;
    QString mExecutable;
    QString mDescription;
    QString mIcon;
    QString mFileName;
    bool mIsReadOnly = false;
};
Q_DECLARE_TYPEINFO(ViewerPluginExternalScriptInfo, Q_RELOCATABLE_TYPE);
Q_DECLARE_METATYPE(ViewerPluginExternalScriptInfo)
