set(pimcommon_boxplugin_SRCS
   boxplugin.cpp
   boxinterface.cpp
)

add_library(pimcommon_boxplugin MODULE ${pimcommon_boxplugin_SRCS} )

target_link_libraries(pimcommon_boxplugin
  KF5::PimCommon KF5::I18n
)

install(TARGETS pimcommon_boxplugin DESTINATION ${PLUGIN_INSTALL_DIR}/pimcommon)
