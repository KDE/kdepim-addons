set(pimcommon_ur1cashorturlengineplugin_SRCS
    ur1cashorturlengineplugin.cpp
    ur1cashorturlengineinterface.cpp
)
ecm_qt_declare_logging_category(pimcommon_ur1cashorturlengineplugin_SRCS HEADER ur1cashorturlengineplugin_debug.h
    IDENTIFIER UR1CASHORTURLENGINEPLUGIN_LOG CATEGORY_NAME log_ur1cashorturlengineplugin)

add_library(pimcommon_ur1cashorturlengineplugin MODULE ${pimcommon_ur1cashorturlengineplugin_SRCS})

target_link_libraries(pimcommon_ur1cashorturlengineplugin
    KF5::Service KF5::I18n Qt5::Network KF5::CoreAddons shorturlpluginprivate
)

install(TARGETS pimcommon_ur1cashorturlengineplugin DESTINATION ${PLUGIN_INSTALL_DIR}/pimcommon)

