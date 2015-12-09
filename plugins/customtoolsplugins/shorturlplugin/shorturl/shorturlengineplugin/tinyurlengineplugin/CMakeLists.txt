set(pimcommon_tinyplugin_SRCS
    tinyurlengineplugin.cpp
    tinyurlengineinterface.cpp
)

add_library(pimcommon_tinyurlengineplugin MODULE ${pimcommon_tinyplugin_SRCS})

target_link_libraries(pimcommon_tinyurlengineplugin
    KF5::Service KF5::I18n Qt5::Network KF5::CoreAddons shorturlpluginprivate
)

install(TARGETS pimcommon_tinyurlengineplugin DESTINATION ${PLUGIN_INSTALL_DIR}/pimcommon)

