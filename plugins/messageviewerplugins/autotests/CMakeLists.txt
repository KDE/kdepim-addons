# SPDX-FileCopyrightText: 2015-2024 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(common_SRCS)
ecm_qt_declare_logging_category(common_SRCS HEADER createeventplugin_debug.h IDENTIFIER CREATEEVENTPLUGIN_LOG CATEGORY_NAME org.kde.pim.createeventplugin)
ecm_qt_declare_logging_category(common_SRCS HEADER createtodoplugin_debug.h IDENTIFIER CREATETODOPLUGIN_LOG CATEGORY_NAME org.kde.pim.createtodoplugin)

macro(add_kdepim_addons_viewerplugin_unittest _source _additional)
    set(_test ${_source}  ${_additional} ${common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_test} ${_name}.h
                 TEST_NAME ${_name}
                 NAME_PREFIX "kdepim-addons-"
                 LINK_LIBRARIES KPim6::MessageViewer KPim6::Libkleo Qt::Test KF6::KIOCore KPim6::Mime
                 KPim6::AkonadiCore KF6::CalendarCore KPim6::GrantleeTheme KPim6::IncidenceEditor
                 KPim6::AkonadiWidgets KF6::XmlGui KPim6::CalendarSupport KF6::TextTranslator
               )

endmacro()



macro(add_kdepim_addons_viewerplugin_class_unittest _source)
    set(_test ${_source} ${common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)

    ecm_add_test(${_test} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "kdepim-addons-"
        LINK_LIBRARIES
            Qt::Test
            KF6::KIOCore
            KF6::CalendarCore
            KPim6::MessageViewer
            KPim6::Libkleo
            KPim6::Mime
            KPim6::AkonadiCore
            KPim6::GrantleeTheme
            KPim6::AkonadiWidgets
            KPim6::CalendarSupport
    )
endmacro()


macro(add_kdepim_addons_viewerplugin_widget_unittest _source _additional)
    set(_test ${_source} ${_additional} ${common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_test} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "kdepim-addons-"
        LINK_LIBRARIES
            Qt::Test
            KF6::KIOCore
            KF6::CalendarCore
            KPim6::MessageViewer
            KPim6::Libkleo
            KPim6::Mime
            KPim6::AkonadiCore
            KPim6::GrantleeTheme
            KPim6::IncidenceEditor
            KPim6::AkonadiWidgets
            KPim6::CalendarSupport
    )
endmacro()


add_kdepim_addons_viewerplugin_class_unittest(viewerpluginmanagertest.cpp)
add_kdepim_addons_viewerplugin_widget_unittest(todoedittest.cpp "../createtodoplugin/todoedit.cpp")
set_tests_properties(kdepim-addons-todoedittest PROPERTIES ENVIRONMENT "LC_ALL=C")

add_kdepim_addons_viewerplugin_widget_unittest(eventedittest.cpp "../createeventplugin/eventedit.cpp;../createeventplugin/eventdatetimewidget.cpp")
add_kdepim_addons_viewerplugin_widget_unittest(eventdatetimewidgettest.cpp "../createeventplugin/eventdatetimewidget.cpp")
add_kdepim_addons_viewerplugin_unittest(viewerplugincreateeventtest.cpp "../createeventplugin/createeventjob.cpp;../createeventplugin/eventdatetimewidget.cpp;../createeventplugin/eventedit.cpp;../createeventplugin/viewerplugincreateevent.cpp;../createeventplugin/viewerplugincreateeventinterface.cpp")
add_kdepim_addons_viewerplugin_unittest(viewerplugincreatetodotest.cpp "../createtodoplugin/viewerplugincreatetodo.cpp;../createtodoplugin/viewerplugincreatetodointerface.cpp;../createtodoplugin/todoedit.cpp;../createtodoplugin/createtodojob.cpp")
add_kdepim_addons_viewerplugin_unittest(viewerplugintranslatortest.cpp "../common/translatorplugin/viewerplugintranslator.cpp;../common/translatorplugin/viewerplugintranslatorinterface.cpp")
