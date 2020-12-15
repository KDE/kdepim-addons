

add_definitions(-DTRANSLATION_DOMAIN=\"messageviewer_text_calendar_plugin\")
set(messageviewer_bodypartformatter_text_calendar_PART_SRCS
    text_calendar.cpp delegateselector.cpp attendeeselector.cpp memorycalendarmemento.cpp syncitiphandler.cpp
    reactiontoinvitationdialog.cpp)

ecm_qt_declare_logging_category(messageviewer_bodypartformatter_text_calendar_PART_SRCS HEADER text_calendar_debug.h IDENTIFIER TEXT_CALENDAR_LOG CATEGORY_NAME org.kde.pim.text_calendar
    DESCRIPTION "kdepim-addons (messageviewer calendar plugins)"
    OLD_CATEGORY_NAMES log_text_calendar
    EXPORT KDEPIMADDONS
    )


qt5_add_dbus_interfaces(messageviewer_bodypartformatter_text_calendar_PART_SRCS
    korganizer/org.kde.Korganizer.Calendar.xml
    )

ki18n_wrap_ui(messageviewer_bodypartformatter_text_calendar_PART_SRCS attendeeselector.ui)

add_library(messageviewer_bodypartformatter_text_calendar MODULE ${messageviewer_bodypartformatter_text_calendar_PART_SRCS})
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_bodypartformatter_text_calendar PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(messageviewer_bodypartformatter_text_calendar
    KF5::KontactInterface
    KF5::Codecs
    Qt5::Core
    KF5::CalendarCore
    KF5::CalendarUtils
    KF5::Mime
    KF5::IdentityManagement
    KF5::MailTransportAkonadi
    KF5::AkonadiMime
    KF5::CalendarSupport
    KF5::PimCommonAkonadi
    KF5::MessageViewer
    KF5::IncidenceEditor
    KF5::PimTextEdit
    KF5::KIOWidgets
    Qt5::DBus
    )

install(TARGETS messageviewer_bodypartformatter_text_calendar  DESTINATION ${KDE_INSTALL_PLUGINDIR}/messageviewer/bodypartformatter)
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
