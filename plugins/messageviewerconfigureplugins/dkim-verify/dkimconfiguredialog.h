/*
   SPDX-FileCopyrightText: 2018-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#ifndef DKIMCONFIGUREDIALOG_H
#define DKIMCONFIGUREDIALOG_H

#include <QDialog>
#include "libdkimverifyconfigure_export.h"

class DKIMConfigureWidget;
class LIBDKIMVERIFYCONFIGURE_EXPORT DKIMConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DKIMConfigureDialog(QWidget *parent = nullptr);
    ~DKIMConfigureDialog() override;

private:
    void slotReset();
    void readConfig();
    void slotAccepted();
    void writeConfig();
    DKIMConfigureWidget *mConfigureWidget = nullptr;
};
#endif // DKIMCONFIGUREDIALOG_H
