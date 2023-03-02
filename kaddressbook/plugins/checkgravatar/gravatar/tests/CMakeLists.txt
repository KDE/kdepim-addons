
set(kaddressbook_checkgravatarplugin_test_SRCS)
ecm_qt_declare_logging_category(kaddressbook_checkgravatarplugin_test_SRCS HEADER kaddressbook_checkgravatarplugin_debug.h IDENTIFIER KADDRESSBOOK_CHECKGRAVATAR_LOG CATEGORY_NAME org.kde.pim.kaddressbook_checkgravatar)

set(gravatarupdatedialog_gui_SRCS ${kaddressbook_checkgravatarplugin_test_SRCS} gravatarupdatedialog_gui.cpp ../widgets/gravatarupdatedialog.cpp ../widgets/gravatarupdatewidget.cpp ../job/gravatarupdatejob.cpp)
add_executable(gravatarupdatedialog_gui ${gravatarupdatedialog_gui_SRCS})
ecm_mark_as_test(gravatarupdatedialog_gui)
target_link_libraries(gravatarupdatedialog_gui
    Qt::Gui
    KF5::PimCommon
    KPim${KF_MAJOR_VERSION}::Gravatar
    KF${KF_MAJOR_VERSION}::I18n
    KPim${KF_MAJOR_VERSION}::AkonadiCore
    KF${KF_MAJOR_VERSION}::Contacts
    )

