set(kmail_changecaseeditorplugin_SRCS
    changecaseplugineditor.cpp
    changecaseplugineditorinterface.cpp
)

ecm_qt_declare_logging_category(kmail_changecaseeditorplugin_SRCS HEADER changecaseeditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_CHANGECASE_PLUGIN_LOG CATEGORY_NAME log_kmail_changecaseeditorplugin)


add_library(kmail_changecaseeditorplugin MODULE ${kmail_changecaseeditorplugin_SRCS})

target_link_libraries(kmail_changecaseeditorplugin
  KF5::IconThemes KF5::MessageComposer KF5::XmlGui
)

install(TARGETS kmail_changecaseeditorplugin DESTINATION ${PLUGIN_INSTALL_DIR}/kmail)

if(BUILD_TESTING)
   add_subdirectory(autotests)
endif()

