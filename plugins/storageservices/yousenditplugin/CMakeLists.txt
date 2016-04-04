set(pimcommon_yousenditplugin_SRCS
   yousenditplugin.cpp
   yousenditinterface.cpp
)

add_library(pimcommon_yousenditplugin MODULE ${pimcommon_yousenditplugin_SRCS} )

target_link_libraries(pimcommon_yousenditplugin
  KF5::PimCommon
  KF5::I18n
)

install(TARGETS pimcommon_yousenditplugin DESTINATION ${PLUGIN_INSTALL_DIR}/pimcommon)
