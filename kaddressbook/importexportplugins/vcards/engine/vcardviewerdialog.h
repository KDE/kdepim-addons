/*
   SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <KContacts/Addressee>
#include <QDialog>

namespace KAddressBookGrantlee
{
class GrantleeContactViewer;
}
class QPushButton;
class VCardViewerDialog : public QDialog
{
    Q_OBJECT
public:
    VCardViewerDialog(const KContacts::Addressee::List &list, QWidget *parent = nullptr);
    ~VCardViewerDialog() override;

    KContacts::Addressee::List contacts() const;

protected Q_SLOTS:
    void slotYes();
    void slotNo();
    void slotApply();
    void slotCancel();

private:
    void readConfig();
    void writeConfig();
    void updateView();

    KContacts::Addressee::List mContacts;
    KContacts::Addressee::List::Iterator mIt;
    QPushButton *mApplyButton = nullptr;
    KAddressBookGrantlee::GrantleeContactViewer *mView = nullptr;
};
