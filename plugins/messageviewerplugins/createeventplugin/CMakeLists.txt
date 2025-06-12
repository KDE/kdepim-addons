# SPDX-FileCopyrightText: 2015-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
kcoreaddons_add_plugin(messageviewer_createeventplugin INSTALL_NAMESPACE pim6/messageviewer/viewerplugin)
target_sources(
    messageviewer_createeventplugin
    PRIVATE
        viewerplugincreateevent.cpp
        viewerplugincreateeventinterface.cpp
        eventedit.cpp
        eventdatetimewidget.cpp
        createeventjob.cpp
        viewerplugincreateevent.h
        viewerplugincreateeventinterface.h
        eventedit.h
        eventdatetimewidget.h
        createeventjob.h
)

ecm_qt_declare_logging_category(messageviewer_createeventplugin HEADER createeventplugin_debug.h IDENTIFIER CREATEEVENTPLUGIN_LOG CATEGORY_NAME org.kde.pim.createeventplugin
    DESCRIPTION "kdepim-addons (create event plugin)"
    OLD_CATEGORY_NAMES log_createeventplugin
    EXPORT KDEPIMADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        messageviewer_createeventplugin
        PROPERTIES UNITY_BUILD ON
    )
endif()

target_link_libraries(
    messageviewer_createeventplugin
    KPim6::MessageViewer
    KF6::XmlGui
    KF6::CalendarCore
    KPim6::IncidenceEditor
    KPim6::AkonadiWidgets
    KPim6::CalendarSupport
)
