set(messageviewer_expireaccounttrashfolderonfigplugin_SRCS
   expireaccounttrashfolderconfigplugin.cpp 
   expireaccounttrashfolderconfigdialog.cpp
   expireaccounttrashfolderconfigwidget.cpp
)

kcoreaddons_add_plugin(messageviewer_expireaccounttrashfolderconfigplugin JSON messageviewer_expireaccounttrashfolderconfigplugin.json SOURCES
    ${messageviewer_expireaccounttrashfolderonfigplugin_SRCS} INSTALL_NAMESPACE messageviewer/configuresettings)

target_link_libraries(messageviewer_expireaccounttrashfolderconfigplugin
  KF5::MessageViewer
  KF5::I18n
  KF5::MailCommon
)


if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
