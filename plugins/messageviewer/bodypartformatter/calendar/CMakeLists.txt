# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_calendar_plugin\")
add_library(messageviewer_bodypartformatter_text_calendar MODULE)

qt_add_dbus_interfaces(messageviewer_bodypartformatter_text_calendar_PART_SRCS
    korganizer/org.kde.Korganizer.Calendar.xml
    )

target_sources(messageviewer_bodypartformatter_text_calendar PRIVATE
    text_calendar.cpp delegateselector.cpp attendeeselector.cpp memorycalendarmemento.cpp syncitiphandler.cpp
    reactiontoinvitationdialog.cpp
    delegateselector.h attendeeselector.h memorycalendarmemento.h syncitiphandler.h
    reactiontoinvitationdialog.h
    ${messageviewer_bodypartformatter_text_calendar_PART_SRCS})

ecm_qt_declare_logging_category(messageviewer_bodypartformatter_text_calendar HEADER text_calendar_debug.h IDENTIFIER TEXT_CALENDAR_LOG CATEGORY_NAME org.kde.pim.text_calendar
    DESCRIPTION "kdepim-addons (messageviewer calendar plugins)"
    OLD_CATEGORY_NAMES log_text_calendar
    EXPORT KDEPIMADDONS
    )



ki18n_wrap_ui(messageviewer_bodypartformatter_text_calendar attendeeselector.ui)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_text_calendar PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_bodypartformatter_text_calendar
    KF${KF_MAJOR_VERSION}::Codecs
    Qt::Core
    KF${KF_MAJOR_VERSION}::CalendarCore
    KF5::CalendarUtils
    KF5::Mime
    KF5::IdentityManagement
    KF5::MailTransportAkonadi
    KF5::MailTransport
    KF5::AkonadiMime
    KF5::CalendarSupport
    KF5::PimCommonAkonadi
    KF5::MessageViewer
    KF5::IncidenceEditor
    KF5::PimTextEdit
    KF${KF_MAJOR_VERSION}::KIOWidgets
    Qt::DBus
    )

install(TARGETS messageviewer_bodypartformatter_text_calendar  DESTINATION ${KDE_INSTALL_PLUGINDIR}/pim${QT_MAJOR_VERSION}/messageviewer/bodypartformatter)
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
