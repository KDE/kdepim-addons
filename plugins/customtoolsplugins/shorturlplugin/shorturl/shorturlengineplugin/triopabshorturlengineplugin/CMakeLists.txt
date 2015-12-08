set(pimcommon_triopabshorturlengineplugin_SRCS
    triopabshorturlengineplugin.cpp
    triopabshorturlengineinterface.cpp
)

add_library(pimcommon_triopabshorturlengineplugin MODULE ${pimcommon_triopabshorturlengineplugin_SRCS})

target_link_libraries(pimcommon_triopabshorturlengineplugin
    KF5::Service KF5::I18n Qt5::Network KF5::CoreAddons shorturlpluginprivate
)

install(TARGETS pimcommon_triopabshorturlengineplugin DESTINATION ${PLUGIN_INSTALL_DIR}/pimcommon)
kcoreaddons_desktop_to_json(pimcommon_triopabshorturlengineplugin pimcommon_triopabshorturlengineplugin.desktop)

