/*
   SPDX-FileCopyrightText: 2016-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef VCARDIMPORTEXPORTPLUGININTERFACE_H
#define VCARDIMPORTEXPORTPLUGININTERFACE_H

#include <KAddressBookImportExport/PluginInterface>
#include <KAddressBookImportExport/ExportSelectionWidget>
#include <KContacts/Addressee>

class VCardImportExportPluginInterface : public KAddressBookImportExport::PluginInterface
{
    Q_OBJECT
public:
    explicit VCardImportExportPluginInterface(QObject *parent = nullptr);
    ~VCardImportExportPluginInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
    Q_REQUIRED_RESULT bool canImportFileType(const QUrl &url) override;
private:
    enum ExportVCardType {
        VCard2_1 = 0,
        VCard3,
        VCard4
    };
    KContacts::Addressee::List parseVCard(const QByteArray &data) const;
    KContacts::Addressee::List filterContacts(const KContacts::Addressee::List &addrList, KAddressBookImportExport::ExportSelectionWidget::ExportFields exportFieldType) const;
    void addKey(KContacts::Addressee &addr, KContacts::Key::Type type) const;

    void exportVCard();
    void importVCard();
    void slotImportVCard();
    void slotExportVCard4();
    void slotExportVCard3();
    Q_REQUIRED_RESULT QString contactFileName(const KContacts::Addressee &contact) const;
    void slotExportVCard2();
    Q_REQUIRED_RESULT bool doExport(const QUrl &url, const QByteArray &data) const;

    ExportVCardType mExportVCardType;
};

#endif // VCARDIMPORTEXPORTPLUGININTERFACE_H
