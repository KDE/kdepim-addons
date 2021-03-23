/*
   SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "libkmailgrammalecte_export.h"
#include <QObject>
class LIBKMAILGRAMMALECTE_EXPORT GrammalecteManager : public QObject
{
    Q_OBJECT
public:
    explicit GrammalecteManager(QObject *parent = nullptr);
    ~GrammalecteManager() override;

    static GrammalecteManager *self();

    Q_REQUIRED_RESULT QString pythonPath() const;
    Q_REQUIRED_RESULT QString grammalectePath() const;

    void setPythonPath(const QString &pythonPath);
    void setGrammalectePath(const QString &grammalectePath);
    Q_REQUIRED_RESULT QStringList options() const;
    void setOptions(const QStringList &saveOptions);

    void loadSettings();
    void saveSettings();

private:
    Q_DISABLE_COPY(GrammalecteManager)
    QStringList mOptions;
    QString mPythonPath;
    QString mGrammalectePath;
};

