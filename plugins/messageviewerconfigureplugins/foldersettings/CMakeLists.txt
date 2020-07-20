set(messageviewer_folderconfiguresettingsplugin_SRCS
   folderconfiguresettingsplugin.cpp
)

kcoreaddons_add_plugin(messageviewer_folderconfiguresettingsplugin JSON messageviewer_folderconfiguresettingsplugin.json SOURCES
    ${messageviewer_folderconfiguresettingsplugin_SRCS} INSTALL_NAMESPACE messageviewer/configuresettings)

target_link_libraries(messageviewer_folderconfiguresettingsplugin
  KF5::MessageViewer
  KF5::I18n
  KF5::MailCommon
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
