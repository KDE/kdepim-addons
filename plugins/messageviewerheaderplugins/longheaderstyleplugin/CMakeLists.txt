set(messageviewer_longheaderstyleplugin_SRCS
   longheaderstyleplugin.cpp
   longheaderstyleinterface.cpp
)

add_library(messageviewer_longheaderstyleplugin MODULE ${messageviewer_longheaderstyleplugin_SRCS})

target_link_libraries(messageviewer_longheaderstyleplugin
  KF5::MessageViewer
  KF5::XmlGui
  KF5::I18n
)

install(TARGETS messageviewer_longheaderstyleplugin DESTINATION ${PLUGIN_INSTALL_DIR}/messageviewer)
