# SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

kcoreaddons_add_plugin(kmail_grammalecteplugin INSTALL_NAMESPACE pim6/kmail/plugineditorgrammar)
target_sources(
    kmail_grammalecteplugin
    PRIVATE
        grammalecteplugin.cpp
        grammalecteinterface.cpp
        grammalecteplugin.h
        grammalecteinterface.h
)

ecm_qt_declare_logging_category(kmail_grammalecteplugin HEADER grammalecteplugin_debug.h IDENTIFIER KMAIL_EDITOR_GRAMMALECTE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_grammalecteplugin
    DESCRIPTION "kdepim-addons (grammalecte plugin)"
    EXPORT KDEPIMADDONS
)

target_link_libraries(
    kmail_grammalecteplugin
    KPim6::MessageComposer
    KF6::I18n
    KPim6::PimCommon
    KF6::XmlGui
    KF6::TextGrammarCheck
)
