set(messageviewer_expandurlplugin_SRCS
    viewerpluginexpandurl.cpp
    viewerpluginexpandurlinterface.cpp
)

if (ECM_VERSION VERSION_LESS "5.68.0")
    ecm_qt_declare_logging_category(messageviewer_expandurlplugin_SRCS HEADER expandurlplugin_debug.h IDENTIFIER EXPANDURLPLUGIN_LOG CATEGORY_NAME org.kde.pim.expandurlplugin)
else()
    ecm_qt_declare_logging_category(messageviewer_expandurlplugin_SRCS HEADER expandurlplugin_debug.h IDENTIFIER EXPANDURLPLUGIN_LOG CATEGORY_NAME org.kde.pim.expandurlplugin
        DESCRIPTION "kdepim-addons (Expand Url Plugin)"
        OLD_CATEGORY_NAMES log_expandurlplugin
        EXPORT KDEPIMADDONS
        )
endif()

kcoreaddons_add_plugin(messageviewer_expandurlplugin JSON messageviewer_expandurlplugin.json SOURCES
    ${messageviewer_expandurlplugin_SRCS} INSTALL_NAMESPACE messageviewer/viewercommonplugin)

target_link_libraries(messageviewer_expandurlplugin
  KF5::MessageViewer KF5::XmlGui KF5::Libkdepim KF5::I18n
)
 
