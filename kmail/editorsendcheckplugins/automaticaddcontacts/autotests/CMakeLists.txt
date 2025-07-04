# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

set(automaticaddcontacts_common_SRCS)
ecm_qt_declare_logging_category(automaticaddcontacts_common_SRCS HEADER automaticaddcontactsplugin_debug.h IDENTIFIER KMAIL_EDITOR_AUTOMATICADDCONTACTS_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_automaticaddcontactsplugin)

macro(add_kmail_automaticaddscontacts_unittest _source _additional)
    set(_test ${_source} ${_additional} ${automaticaddcontacts_common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(kmail_editorplugin-${_name})
    target_link_libraries(
        ${_name}
        Qt::Test
        KPim6::MessageComposer
        KF6::I18n
        KF6::Codecs
        KPim6::PimCommon
        KPim6::AkonadiContactWidgets
    )
endmacro()

if(KDEPIM_RUN_AKONADI_TEST)
    set(KDEPIMLIBS_RUN_ISOLATED_TESTS TRUE)
    set(KDEPIMLIBS_RUN_SQLITE_ISOLATED_TESTS TRUE)

    add_akonadi_isolated_test_advanced(automaticaddcontactsplugintest.cpp "${automaticaddcontacts_common_SRCS};../automaticaddcontactsconfiguredialog.cpp;../automaticaddcontactsconfigurewidget.cpp;../automaticaddcontactsconfiguretab.cpp;../automaticaddcontactstabwidget.cpp;../automaticaddcontactsjob.cpp;../automaticaddcontactsplugin.cpp;../automaticaddcontactsinterface.cpp;../automaticaddcontactsconfigurewidget.cpp" "KPim6::MessageComposer;KF6::I18n;KPim6::PimCommon;KPim6::AkonadiContactWidgets;KF6::Codecs")
    add_akonadi_isolated_test_advanced(automaticaddcontactsconfigurewidgettest.cpp "${automaticaddcontacts_common_SRCS};../automaticaddcontactsconfiguretab.cpp;../automaticaddcontactstabwidget.cpp;../automaticaddcontactsconfigurewidget.cpp" "KPim6::MessageComposer;KF6::I18n;KPim6::PimCommon;KPim6::AkonadiContactCore")
    add_akonadi_isolated_test_advanced(automaticaddcontactstabwidgettest.cpp "${automaticaddcontacts_common_SRCS};../automaticaddcontactstabwidget.cpp" "KPim6::MessageComposer;KF6::I18n;KPim6::PimCommon;KPim6::AkonadiContactCore")
    add_akonadi_isolated_test_advanced(automaticaddcontactsconfiguretabtest.cpp "${automaticaddcontacts_common_SRCS};../automaticaddcontactstabwidget.cpp;../automaticaddcontactsconfiguretab.cpp" "KPim6::MessageComposer;KF6::I18n;KPim6::PimCommon;KPim6::AkonadiContactCore")
endif()

add_kmail_automaticaddscontacts_unittest(automaticaddcontactsjobtest.cpp "../automaticaddcontactsjob.cpp" "KPim6::MessageComposer;KF6::I18n;KPim6::PimCommon;KPim6::AkonadiContactCore;KF6::Codecs")
