# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
include_directories(${CMAKE_CURRENT_BINARY_DIR})
kcoreaddons_add_plugin(imapfoldercompletionplugin INSTALL_NAMESPACE pim6/libksieve)

set(sieveeditor_plugin_categories_SRCS)
ecm_qt_declare_logging_category(sieveeditor_plugin_categories_SRCS HEADER imapfoldercompletionplugin_debug.h IDENTIFIER
    IMAPFOLDERCOMPLETIONPLUGIN_LOG CATEGORY_NAME org.kde.pim.imapfoldercompletion
    DESCRIPTION "kdepim-addons (SieveEditor imap completion folder)"
    EXPORT KDEPIMADDONS
    )


if(BUILD_TESTING)
    add_subdirectory(tests)
    add_subdirectory(autotests)
endif()


target_sources(imapfoldercompletionplugin PRIVATE
    selectimapfolderdialog.cpp
    selectimapfolderwidget.cpp
    selectimapwidget.cpp
    selectimaploadfoldersjob.cpp
    selectimapfoldermodel.cpp
    selectimaplineedit.cpp
    selectimaplineeditcompletermodel.cpp
    selectimapcreatefolderjob.cpp
    selectimapfoldertreeview.cpp
    ${sieveeditor_plugin_categories_SRCS}
    selectimapfolderdialog.h
    selectimapfolderwidget.h
    selectimapwidget.h
    selectimaploadfoldersjob.h
    selectimapfoldermodel.h
    selectimaplineedit.h
    selectimaplineeditcompletermodel.h
    selectimapcreatefolderjob.h
    selectimapfoldertreeview.h
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(imapfoldercompletionplugin PROPERTIES UNITY_BUILD ON)
endif()
target_link_libraries(imapfoldercompletionplugin
    KPim6::PimCommon KF6::Completion KF6::I18n KF6::KIOWidgets KPim6::KSieveUi KPim6::MailTransport KPim6::IMAP KF6::ItemModels
    )
