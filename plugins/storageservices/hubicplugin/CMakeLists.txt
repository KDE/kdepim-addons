set(pimcommon_hubicplugin_SRCS
   hubicplugin.cpp
   hubicinterface.cpp
)

add_library(pimcommon_hubicplugin MODULE ${pimcommon_hubicplugin_SRCS} )

target_link_libraries(pimcommon_hubicplugin
  KF5::PimCommon
  KF5::I18n
)

install(TARGETS pimcommon_hubicplugin DESTINATION ${PLUGIN_INSTALL_DIR}/pimcommon)
