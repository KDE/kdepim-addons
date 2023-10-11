kcoreaddons_add_plugin(messageviewer_enterpriseheaderstyleplugin JSON ${CMAKE_CURRENT_BINARY_DIR}/messageviewer_enterpriseheaderstyleplugin.json INSTALL_NAMESPACE messageviewer)
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/messageviewer_enterpriseheaderstyleplugin.json.in
        ${CMAKE_CURRENT_BINARY_DIR}/messageviewer_enterpriseheaderstyleplugin.json)

   
target_sources(messageviewer_enterpriseheaderstyleplugin PRIVATE
   enterpriseheaderstyleplugin.cpp
   enterpriseheaderstyleinterface.cpp 
   enterpriseheaderstyle.cpp
)


target_link_libraries(messageviewer_enterpriseheaderstyleplugin
  KPim6::MessageViewer 
  KF6::XmlGui
  KF6::I18n
)
