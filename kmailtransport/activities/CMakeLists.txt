# SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(${CMAKE_CURRENT_BINARY_DIR})
kcoreaddons_add_plugin(kmailtransportactivitiesplugin INSTALL_NAMESPACE "pim6/mailtransportactivities")

ecm_qt_declare_logging_category(kmailtransportactivitiesplugin HEADER kmailtransportactivitiesplugin_debug.h IDENTIFIER
    KMAILTRANSPORTACTIVITIES_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmailtransportactivitiesplugin
    DESCRIPTION "kdepim-addons (KMailtransport activities support)"
    EXPORT KDEPIMADDONS
)

target_sources(kmailtransportactivitiesplugin PRIVATE
    transportactivitiesplugin.h
    transportactivitiesplugin.cpp
)

target_link_libraries(kmailtransportactivitiesplugin
        KF6::I18n KF6::CoreAddons KPim6::MailTransport Qt::Widgets KPim6::PimCommonActivities
)
