# SPDX-FileCopyrightText: 2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(kmailconfirmbeforedeleting)

target_sources(kmailconfirmbeforedeleting PRIVATE
    confirmbeforedeletingdialog.cpp
    confirmbeforedeletingwidget.cpp
    confirmbeforedeletingmanager.cpp
    confirmbeforedeletingrule.cpp
    confirmbeforedeletingcreateruledialog.cpp
    confirmbeforedeletingcreaterulewidget.cpp
    )
ecm_qt_declare_logging_category(kmailconfirmbeforedeleting HEADER confirmbeforedeletingplugin_debug.h IDENTIFIER KMAIL_CONFIRMBEFOREDELETING_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_confirmbeforedeletingplugin
    DESCRIPTION "kdepim-addons (Confirm Before Deleting email)"
    OLD_CATEGORY_NAMES log_kmail_confirmbeforedeletingplugin
    EXPORT KDEPIMADDONS
    )



if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmailconfirmbeforedeleting PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(kmailconfirmbeforedeleting BASE_NAME kmailconfirmbeforedeleting)
target_link_libraries(kmailconfirmbeforedeleting
    KF5::MessageViewer
    KF5::I18n
)

set_target_properties(kmailconfirmbeforedeleting
    PROPERTIES OUTPUT_NAME kmailconfirmbeforedeleting VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )


install(TARGETS kmailconfirmbeforedeleting ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)



if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
kcoreaddons_add_plugin(kmail_confirmbeforedeletingplugin INSTALL_NAMESPACE messageviewer/checkbeforedeleting)
target_sources(kmail_confirmbeforedeletingplugin PRIVATE
    confirmbeforedeletinginterface.cpp
    confirmbeforedeletingplugin.cpp
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_confirmbeforedeletingplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_confirmbeforedeletingplugin
    KF5::MessageViewer KF5::I18n KF5::PimCommon KF5::Libkdepim kmailconfirmbeforedeleting
    )
