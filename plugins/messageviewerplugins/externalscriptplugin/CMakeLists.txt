set(messageviewer_externalscriptplugin_SRCS
    viewerpluginexternalscript.cpp  
    viewerpluginexternalscriptinterface.cpp
    viewerpluginexternalscriptmanager.cpp
    viewerpluginexternalscriptinfo.cpp
    viewerpluginexternalscriptsloadjob.cpp
    viewerpluginexternalscriptparseargument.cpp
)

ecm_qt_declare_logging_category(messageviewer_externalscriptplugin_SRCS HEADER externalscriptplugin_debug.h IDENTIFIER EXTERNALSCRIPTPLUGIN_LOG CATEGORY_NAME org.kde.pim.externalscriptplugin)
kcoreaddons_add_plugin(messageviewer_externalscriptplugin JSON messageviewer_externalscriptplugin.json SOURCES ${messageviewer_externalscriptplugin_SRCS} INSTALL_NAMESPACE messageviewer)

target_link_libraries(messageviewer_externalscriptplugin
  KF5::MessageViewer KF5::XmlGui KF5::I18n
)

if (KDEPIMADDONS_BUILD_EXAMPLES)
   add_subdirectory(examples)
endif() 
