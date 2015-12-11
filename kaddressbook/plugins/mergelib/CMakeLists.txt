set(kaddressbookmergelibprivate_SRCS
   job/searchpotentialduplicatecontactjob.cpp
   job/mergecontactsjob.cpp
   job/mergecontacts.cpp

   manualmerge/mergecontactsdialog.cpp
   manualmerge/mergecontactwidget.cpp
   manualmerge/mergecontactwidgetlist.cpp

   searchduplicate/searchandmergecontactduplicatecontactdialog.cpp
   searchduplicate/searchduplicateresultwidget.cpp
   searchduplicate/resultduplicatetreewidget.cpp
   searchduplicate/mergecontactselectinformationtabwidget.cpp

   widgets/mergecontactinfowidget.cpp
   widgets/mergecontactshowresulttabwidget.cpp
   widgets/mergecontactselectinformationwidget.cpp
   widgets/mergecontactselectlistwidget.cpp
   widgets/mergecontactloseinformationwarning.cpp
   widgets/mergecontactselectinformationscrollarea.cpp
   widgets/mergecontacterrorlabel.cpp
)
ecm_qt_declare_logging_category(kaddressbookmergelibprivate_SRCS HEADER kaddressbookmergelibprivate_debug.h IDENTIFIER KADDRESSBOOKMERGELIBPRIVATE_LOG CATEGORY_NAME log_kaddressbookmergelibprivate)

add_library(kaddressbookmergelibprivate ${kaddressbookmergelibprivate_SRCS})
generate_export_header(kaddressbookmergelibprivate BASE_NAME kaddressbookmergelib)


target_link_libraries(kaddressbookmergelibprivate
PRIVATE
    Qt5::Network KF5::I18n KF5::KaddressbookGrantlee KF5::Contacts KF5::AkonadiContact KF5::ConfigCore KF5::WidgetsAddons KF5::AkonadiWidgets
)

set_target_properties(kaddressbookmergelibprivate
    PROPERTIES VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(TARGETS kaddressbookmergelibprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)


if (BUILD_TESTING)
   add_subdirectory(autotests)
endif()
