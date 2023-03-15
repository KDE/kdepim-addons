add_library(pimcommon_googleshorturlengineplugin MODULE)
target_sources(pimcommon_googleshorturlengineplugin PRIVATE
    googleshorturlengineplugin.cpp
    googleshorturlengineinterface.cpp
)


target_link_libraries(pimcommon_googleshorturlengineplugin
  KPim${KF_MAJOR_VERSION}::PimCommon
)

install(TARGETS pimcommon_googleshorturlengineplugin DESTINATION ${KDE_INSTALL_PLUGINDIR}/pimcommon)
kcoreaddons_desktop_to_json(pimcommon_googleshorturlengineplugin pimcommon_googleshorturlengineplugin.desktop)

