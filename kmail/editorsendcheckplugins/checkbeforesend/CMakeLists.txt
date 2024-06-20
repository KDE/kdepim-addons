# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/
)
kcoreaddons_add_plugin(kmail_checkbeforesendeditorplugin INSTALL_NAMESPACE pim6/kmail/plugincheckbeforesend)

target_sources(kmail_checkbeforesendeditorplugin PRIVATE
    checkbeforesendplugin.cpp
    checkbeforesendinterface.cpp
    checkbeforesendupdatesmtpdialog.cpp
    configurewidget/checkbeforesendconfigurewidget.cpp
    configurewidget/checkbeforesendconfiguredialog.cpp
    duplicateemails/checkduplicateemailsdialog.cpp
    duplicateemails/checkduplicateemailsjob.cpp
    sendattachments/checkattachmentdialog.cpp
    sendattachments/checkattachmentjob.cpp
    checkbeforesendplugin.h
    checkbeforesendinterface.h
    checkbeforesendupdatesmtpdialog.h
    configurewidget/checkbeforesendconfigurewidget.h
    configurewidget/checkbeforesendconfiguredialog.h
    duplicateemails/checkduplicateemailsdialog.h
    duplicateemails/checkduplicateemailsjob.h
    sendattachments/checkattachmentdialog.h
    sendattachments/checkattachmentjob.h
)

ecm_qt_declare_logging_category(kmail_checkbeforesendeditorplugin HEADER checkbeforesendplugin_debug.h IDENTIFIER KMAIL_EDITOR_checkbeforesend_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_checkbeforesendplugin
    DESCRIPTION "kdepim-addons (check before send editor plugin)"
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_checkbeforesendeditorplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_checkbeforesendeditorplugin
    KPim6::MessageComposer KF6::I18n KF6::Codecs
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
