# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
set(common_SRCS)
ecm_qt_declare_logging_category(common_SRCS HEADER createeventplugin_debug.h IDENTIFIER CREATEEVENTPLUGIN_LOG CATEGORY_NAME org.kde.pim.createeventplugin)
ecm_qt_declare_logging_category(common_SRCS HEADER createnoteplugin_debug.h IDENTIFIER CREATENOTEPLUGIN_LOG CATEGORY_NAME org.kde.pim.createnoteplugin)
ecm_qt_declare_logging_category(common_SRCS HEADER createtodoplugin_debug.h IDENTIFIER CREATETODOPLUGIN_LOG CATEGORY_NAME org.kde.pim.createtodoplugin)

macro(add_kdepim_addons_viewerplugin_unittest _source _additional)
    set( _test ${_source}  ${_additional} ${common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    if (USE_KTEXTADDONS_LIB)
        set(TEXTTRANSLATE_LIBS KF5::TextTranslator)
    else()
        set(TEXTTRANSLATE_LIBS KF5::PimCommonTextTranslator)
    endif()
    ecm_add_test(${_test} ${_name}.h
                 TEST_NAME ${_name}
                 NAME_PREFIX "kdepim-addons-"
                 LINK_LIBRARIES KF5::MessageViewer KF5::Libkleo Qt::Test KF${KF_MAJOR_VERSION}::KIOCore KF5::Mime
                 KF5::AkonadiCore KF5::AkonadiNotes KF${KF_MAJOR_VERSION}::CalendarCore KF5::GrantleeTheme KF5::IncidenceEditor
                 KF5::AkonadiWidgets KF${KF_MAJOR_VERSION}::XmlGui KF5::CalendarSupport ${TEXTTRANSLATE_LIBS}
                )

endmacro ()



macro(add_kdepim_addons_viewerplugin_class_unittest _source )
    set( _test ${_source} ${common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)

    ecm_add_test(${_test} ${_name}.h
                 TEST_NAME ${_name}
                 NAME_PREFIX "kdepim-addons-"
		 LINK_LIBRARIES KF5::MessageViewer KF5::Libkleo Qt::Test KF${KF_MAJOR_VERSION}::KIOCore KF5::Mime KF5::AkonadiCore KF5::AkonadiNotes KF${KF_MAJOR_VERSION}::CalendarCore KF5::GrantleeTheme KF5::AkonadiWidgets KF5::CalendarSupport
                )
endmacro ()


macro(add_kdepim_addons_viewerplugin_widget_unittest _source _additional )
    set( _test ${_source} ${_additional} ${common_SRCS})
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_test} ${_name}.h
                 TEST_NAME ${_name}
                 NAME_PREFIX "kdepim-addons-"
                 LINK_LIBRARIES KF5::MessageViewer KF5::Libkleo Qt::Test KF${KF_MAJOR_VERSION}::KIOCore KF5::Mime KF5::AkonadiCore KF5::AkonadiNotes KF${KF_MAJOR_VERSION}::CalendarCore KF5::GrantleeTheme KF5::IncidenceEditor KF5::AkonadiWidgets KF5::CalendarSupport)
endmacro ()


add_kdepim_addons_viewerplugin_class_unittest(viewerpluginmanagertest.cpp)
add_kdepim_addons_viewerplugin_widget_unittest(todoedittest.cpp "../createtodoplugin/todoedit.cpp")
add_kdepim_addons_viewerplugin_widget_unittest(noteedittest.cpp "../createnoteplugin/noteedit.cpp")
set_tests_properties(kdepim-addons-todoedittest PROPERTIES ENVIRONMENT "LC_ALL=C")

add_kdepim_addons_viewerplugin_widget_unittest(eventedittest.cpp "../createeventplugin/eventedit.cpp;../createeventplugin/eventdatetimewidget.cpp")
add_kdepim_addons_viewerplugin_widget_unittest(eventdatetimewidgettest.cpp "../createeventplugin/eventdatetimewidget.cpp")
add_kdepim_addons_viewerplugin_unittest(viewerplugincreateeventtest.cpp "../createeventplugin/createeventjob.cpp;../createeventplugin/eventdatetimewidget.cpp;../createeventplugin/eventedit.cpp;../createeventplugin/viewerplugincreateevent.cpp;../createeventplugin/viewerplugincreateeventinterface.cpp")
add_kdepim_addons_viewerplugin_unittest(viewerplugincreatetodotest.cpp "../createtodoplugin/viewerplugincreatetodo.cpp;../createtodoplugin/viewerplugincreatetodointerface.cpp;../createtodoplugin/todoedit.cpp;../createtodoplugin/createtodojob.cpp")
add_kdepim_addons_viewerplugin_unittest(viewerplugincreatenotetest.cpp "../createnoteplugin/noteedit.cpp;../createnoteplugin/viewerplugincreatenote.cpp;../createnoteplugin/viewerplugincreatenoteinterface.cpp;../createnoteplugin/createnotejob.cpp")
add_kdepim_addons_viewerplugin_unittest(viewerplugintranslatortest.cpp "../common/translatorplugin/viewerplugintranslator.cpp;../common/translatorplugin/viewerplugintranslatorinterface.cpp")
