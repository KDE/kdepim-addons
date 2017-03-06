include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

set(kaddressbook_gravatar_SRCS
   gravatar/job/gravatarupdatejob.cpp
   gravatar/widgets/gravatarupdatedialog.cpp
   gravatar/widgets/gravatarupdatewidget.cpp
)

set(kaddressbook_checkgravatarplugin_SRCS
    checkgravatarplugininterface.cpp
    checkgravatarplugin.cpp
    ${kaddressbook_gravatar_SRCS}
)

ecm_qt_declare_logging_category(kaddressbook_checkgravatarplugin_SRCS HEADER kaddressbook_checkgravatarplugin_debug.h IDENTIFIER KADDRESSBOOK_CHECKGRAVATAR_LOG CATEGORY_NAME org.kde.pim.kaddressbook_checkgravatar)

kcoreaddons_add_plugin(kaddressbook_checkgravatarplugin JSON kaddressbook_checkgravatarplugin.json SOURCES
    ${kaddressbook_checkgravatarplugin_SRCS} INSTALL_NAMESPACE kaddressbook)

target_link_libraries(kaddressbook_checkgravatarplugin
	KF5::PimCommon KF5::Completion KF5::IconThemes KF5::PimCommonAkonadi KF5::XmlGui KF5::Gravatar KF5::I18n KF5::Contacts
)

if (BUILD_TESTING)
   add_subdirectory(gravatar/autotests)
   add_subdirectory(gravatar/tests)
endif()
