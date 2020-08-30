/*
   SPDX-FileCopyrightText: 2016-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VIEWERPLUGINEXTERNALSCRIPTINFO_H
#define VIEWERPLUGINEXTERNALSCRIPTINFO_H

#include <QString>
#include <QObject>
class ViewerPluginExternalScriptInfo
{
public:
    ViewerPluginExternalScriptInfo();
    QString name() const;
    void setName(const QString &name);

    QString commandLine() const;
    void setCommandLine(const QString &commandLine);

    QString executable() const;
    void setExecutable(const QString &executable);

    QString description() const;
    void setDescription(const QString &description);

    QString icon() const;
    void setIcon(const QString &icon);

    bool isValid() const;

    bool isReadOnly() const;
    void setIsReadOnly(bool isReadOnly);

    QString fileName() const;
    void setFileName(const QString &fileName);

    bool operator==(const ViewerPluginExternalScriptInfo &other) const;
private:
    QString mCommandLine;
    QString mName;
    QString mExecutable;
    QString mDescription;
    QString mIcon;
    QString mFileName;
    bool mIsReadOnly = false;
};
Q_DECLARE_TYPEINFO(ViewerPluginExternalScriptInfo, Q_MOVABLE_TYPE);
Q_DECLARE_METATYPE(ViewerPluginExternalScriptInfo)

#endif // VIEWERPLUGINEXTERNALSCRIPTINFO_H
