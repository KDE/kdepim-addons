set(messageviewer_expandurlplugin_SRCS
    viewerpluginexpandurl.cpp
    viewerpluginexpandurlinterface.cpp
    )

ecm_qt_declare_logging_category(messageviewer_expandurlplugin_SRCS HEADER expandurlplugin_debug.h IDENTIFIER EXPANDURLPLUGIN_LOG CATEGORY_NAME org.kde.pim.expandurlplugin
    DESCRIPTION "kdepim-addons (Expand Url Plugin)"
    OLD_CATEGORY_NAMES log_expandurlplugin
    EXPORT KDEPIMADDONS
    )

kcoreaddons_add_plugin(messageviewer_expandurlplugin JSON messageviewer_expandurlplugin.json SOURCES
    ${messageviewer_expandurlplugin_SRCS} INSTALL_NAMESPACE messageviewer/viewercommonplugin)
if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(messageviewer_expandurlplugin PROPERTIES UNITY_BUILD ON)
endif()
target_link_libraries(messageviewer_expandurlplugin
    KF5::MessageViewer KF5::XmlGui KF5::Libkdepim KF5::I18n
    )

