kcoreaddons_add_plugin(messageviewer_enterpriseheaderstyleplugin JSON ${CMAKE_CURRENT_BINARY_DIR}/messageviewer_enterpriseheaderstyleplugin.json INSTALL_NAMESPACE messageviewer)
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/messageviewer_enterpriseheaderstyleplugin.json.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/messageviewer_enterpriseheaderstyleplugin.json)

   
target_sources(messageviewer_enterpriseheaderstyleplugin PRIVATE
   enterpriseheaderstyleplugin.cpp
   enterpriseheaderstyleinterface.cpp 
   enterpriseheaderstyle.cpp
)


target_link_libraries(messageviewer_enterpriseheaderstyleplugin
  KF5::MessageViewer 
  KF5::XmlGui
  KF5::I18n
)
