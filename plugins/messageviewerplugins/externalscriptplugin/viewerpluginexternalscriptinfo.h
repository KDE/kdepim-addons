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
    [[nodiscard]] QString name() const;
    void setName(const QString &name);

    [[nodiscard]] QString commandLine() const;
    void setCommandLine(const QString &commandLine);

    [[nodiscard]] QString executable() const;
    void setExecutable(const QString &executable);

    [[nodiscard]] QString description() const;
    void setDescription(const QString &description);

    [[nodiscard]] QString icon() const;
    void setIcon(const QString &icon);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] bool isReadOnly() const;
    void setIsReadOnly(bool isReadOnly);

    [[nodiscard]] QString fileName() const;
    void setFileName(const QString &fileName);

    [[nodiscard]] bool operator==(const ViewerPluginExternalScriptInfo &other) const;

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
