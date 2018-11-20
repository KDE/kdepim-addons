set(messageviewer_gravatarconfigplugin_SRCS
   gravatarconfiguresettingspluginwidget.cpp
   gravatarconfiguresettingsplugin.cpp
   gravatarconfiguresettingsplugindialog.cpp
)

kcoreaddons_add_plugin(messageviewer_gravatarconfigplugin JSON messageviewer_gravatarconfigplugin.json SOURCES
    ${messageviewer_gravatarconfigplugin_SRCS} INSTALL_NAMESPACE messageviewer)

target_link_libraries(messageviewer_gravatarconfigplugin
  KF5::MessageViewer
  KF5::PimCommon
  KF5::Gravatar
  KF5::I18n
)

add_subdirectory(autotests)
