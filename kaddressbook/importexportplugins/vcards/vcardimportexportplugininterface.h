/*
   SPDX-FileCopyrightText: 2016-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <KAddressBookImportExport/ExportSelectionWidget>
#include <KAddressBookImportExport/PluginInterface>
#include <KContacts/Addressee>

class VCardImportExportPluginInterface : public KAddressBookImportExport::PluginInterface
{
    Q_OBJECT
public:
    explicit VCardImportExportPluginInterface(QObject *parent = nullptr);
    ~VCardImportExportPluginInterface() override;

    void createAction(KActionCollection *ac) override;
    void exec() override;
    [[nodiscard]] bool canImportFileType(const QUrl &url) override;

private:
    enum ExportVCardType {
        VCard2_1 = 0,
        VCard3,
        VCard4,
    };
    KContacts::Addressee::List parseVCard(const QByteArray &data) const;
    KContacts::Addressee::List filterContacts(const KContacts::Addressee::List &addrList,
                                              KAddressBookImportExport::ExportSelectionWidget::ExportFields exportFieldType) const;
    void addKey(KContacts::Addressee &addr, KContacts::Key::Type type) const;

    void exportVCard();
    void importVCard();
    void slotImportVCard();
    void slotExportVCard4();
    void slotExportVCard3();
    [[nodiscard]] QString contactFileName(const KContacts::Addressee &contact) const;
    void slotExportVCard2();
    [[nodiscard]] bool doExport(const QUrl &url, const QByteArray &data) const;

    ExportVCardType mExportVCardType;
};
