set(pimcommon_translatorplugin_SRCS
   translatorplugin.cpp
   translatorview.cpp
)

kcoreaddons_add_plugin(pimcommon_translatorplugin JSON pimcommon_translatorplugin.json SOURCES
    ${pimcommon_translatorplugin_SRCS} INSTALL_NAMESPACE pimcommon)

target_link_libraries(pimcommon_translatorplugin
  KF5::PimCommon
  KF5::PimTextEdit
  KF5::XmlGui
  KF5::I18n
)
