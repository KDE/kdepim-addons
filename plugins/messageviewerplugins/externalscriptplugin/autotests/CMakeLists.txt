# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions (-DTEST_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/externaldatas")

ecm_qt_declare_logging_category(common_SRCS HEADER externalscriptplugin_debug.h IDENTIFIER EXTERNALSCRIPTPLUGIN_LOG CATEGORY_NAME org.kde.pim.externalscriptplugin)

macro(add_messageviewer_viewerplugin_external_plugin_unittest _source _additional _jsonfile)
    set( _test ${_source}  ${_additional} ${common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    if (${_jsonfile})
       kcoreaddons_desktop_to_json(${_name} ${_jsonfile})
    endif()
    ecm_add_test(${_test}
                 TEST_NAME ${_name}
                 NAME_PREFIX "messageviewerplugins-"
                 LINK_LIBRARIES KPim${KF_MAJOR_VERSION}::MessageViewer Qt::Test KF${KF_MAJOR_VERSION}::KIOCore KPim${KF_MAJOR_VERSION}::Mime KPim${KF_MAJOR_VERSION}::AkonadiCore KF${KF_MAJOR_VERSION}::I18n KF${KF_MAJOR_VERSION}::XmlGui KPim${KF_MAJOR_VERSION}::PimCommon KF${KF_MAJOR_VERSION}::KIOWidgets KPim${KF_MAJOR_VERSION}::Libkdepim
                )
endmacro ()


add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscriptinfotest.cpp "../viewerpluginexternalscriptparseargument.cpp;../viewerpluginexternalscriptinfo.cpp;../viewerpluginexternalscriptsloadjob.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscriptsloadjobtest.cpp "../viewerpluginexternalscriptsloadjob.cpp;../viewerpluginexternalscriptinfo.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscriptparseargumenttest.cpp "../viewerpluginexternalscriptparseargument.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalconfigurewidgettest.cpp "../configuredialog/viewerpluginexternaleditwidget.cpp;../configuredialog/viewerpluginexternaleditdialog.cpp;../configuredialog/viewerpluginexternalconfigurewidget.cpp;../viewerpluginexternalscriptsloadjob.cpp;../viewerpluginexternalscriptinfo.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalconfiguredialogtest.cpp "../configuredialog/viewerpluginexternaleditwidget.cpp;../configuredialog/viewerpluginexternaleditdialog.cpp;../configuredialog/viewerpluginexternalconfiguredialog.cpp;../configuredialog/viewerpluginexternalconfigurewidget.cpp;../viewerpluginexternalscriptsloadjob.cpp;../viewerpluginexternalscriptinfo.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternaleditwidgettest.cpp "../viewerpluginexternalscriptinfo.cpp;../configuredialog/viewerpluginexternaleditwidget.cpp" "")
add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternaleditdialogtest.cpp "../viewerpluginexternalscriptinfo.cpp;../configuredialog/viewerpluginexternaleditdialog.cpp;../configuredialog/viewerpluginexternaleditwidget.cpp" "")
#add_messageviewer_viewerplugin_external_plugin_unittest(viewerpluginexternalscripttest.cpp "../viewerpluginexternalscriptparseargument.cpp;../viewerpluginexternalscript.cpp;../viewerpluginexternalscriptinterface.cpp;../viewerpluginexternalscriptinfo.cpp;../configuredialog/viewerpluginexternaleditdialog.cpp;../configuredialog/viewerpluginexternaleditwidget.cpp;../configuredialog/viewerpluginexternaleditwidget.cpp;../configuredialog/viewerpluginexternaleditdialog.cpp;../configuredialog/viewerpluginexternalconfigurewidget.cpp;../viewerpluginexternalscriptsloadjob.cpp;../viewerpluginexternalscriptinfo.cpp" "")
