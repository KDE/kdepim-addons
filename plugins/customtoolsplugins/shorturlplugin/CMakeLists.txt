set(shorturlpluginprivate_SRCS
    shorturl/shorturlengineplugin/shorturlengineinterface.cpp
    shorturl/shorturlengineplugin/shorturlengineplugin.cpp
)


add_library(shorturlpluginprivate ${shorturlpluginprivate_SRCS})
generate_export_header(shorturlpluginprivate BASE_NAME shorturl)

target_link_libraries(shorturlpluginprivate
PRIVATE
    Qt5::Network KF5::I18n
)

set_target_properties(shorturlpluginprivate
    PROPERTIES VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
)

install(TARGETS shorturlpluginprivate ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)


set(pimcommon_shorturlplugin_SRCS
   shorturlplugin.cpp
   shorturlview.cpp
)

set(pimcommon_shorturlplugin_shorturllib_SRCS
   shorturl/shorturlwidgetng.cpp
   shorturl/shorturlconfigurewidget.cpp
   shorturl/shorturlconfiguredialog.cpp
   shorturl/shorturlengineplugin/shorturlenginepluginmanager.cpp
)

add_library(pimcommon_shorturlplugin MODULE ${pimcommon_shorturlplugin_SRCS} ${pimcommon_shorturlplugin_shorturllib_SRCS})

target_link_libraries(pimcommon_shorturlplugin
  KF5::PimCommon KF5::XmlGui KF5::Completion KF5::KIOWidgets KF5::Libkdepim shorturlpluginprivate
)

install(TARGETS pimcommon_shorturlplugin DESTINATION ${PLUGIN_INSTALL_DIR}/pimcommon)

add_subdirectory(shorturl)
