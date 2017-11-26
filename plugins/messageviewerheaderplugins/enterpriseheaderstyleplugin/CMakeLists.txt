configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/messageviewer_enterpriseheaderstyleplugin.json.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/messageviewer_enterpriseheaderstyleplugin.json)

   
set(messageviewer_enterpriseheaderstyleplugin_SRCS
   enterpriseheaderstyleplugin.cpp
   enterpriseheaderstyleinterface.cpp 
   enterpriseheaderstyle.cpp
)

kcoreaddons_add_plugin(messageviewer_enterpriseheaderstyleplugin JSON ${CMAKE_CURRENT_BINARY_DIR}/messageviewer_enterpriseheaderstyleplugin.json SOURCES
    ${messageviewer_enterpriseheaderstyleplugin_SRCS} INSTALL_NAMESPACE messageviewer)

target_link_libraries(messageviewer_enterpriseheaderstyleplugin
  KF5::MessageViewer 
  KF5::XmlGui
  KF5::I18n
)
