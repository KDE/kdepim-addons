set(pimcommon_gdriveplugin_SRCS
   gdriveplugin.cpp
   gdriveinterface.cpp
)

add_library(pimcommon_gdriveplugin MODULE ${pimcommon_gdriveplugin_SRCS} )

target_link_libraries(pimcommon_gdriveplugin
  KF5::PimCommon
  KF5::I18n
)

install(TARGETS pimcommon_gdriveplugin DESTINATION ${PLUGIN_INSTALL_DIR}/pimcommon)
