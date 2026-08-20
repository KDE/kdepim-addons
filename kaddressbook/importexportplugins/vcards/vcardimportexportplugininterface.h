/*
   SPDX-FileCopyrightText: 2016-2026 Laurent Montel <montel@kde.org>

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
    void importFile(const QUrl &url) override;

private:
    KContacts::Addressee::List parseVCard(const QByteArray &data) const;
    KContacts::Addressee::List filterContacts(const KContacts::Addressee::List &addrList,
                                              KAddressBookImportExport::ExportSelectionWidget::ExportFields exportFieldType) const;
    void addKey(KContacts::Addressee &addr, KContacts::Key::Type type) const;

    void exportVCard();
    void importVCard();
    void importVCards(const QList<QUrl> &urls);
    void slotImportVCard();
    void slotExportVCard();
    [[nodiscard]] QString contactFileName(const KContacts::Addressee &contact) const;
    [[nodiscard]] bool doExport(const QUrl &url, const QByteArray &data) const;
};
