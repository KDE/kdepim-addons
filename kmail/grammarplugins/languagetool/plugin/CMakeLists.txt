if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

kcoreaddons_add_plugin(kmail_languagetoolplugin INSTALL_NAMESPACE kmail/plugineditorgrammar)
target_sources(kmail_languagetoolplugin PRIVATE
    languagetoolplugin.cpp
    languagetoolinterface.cpp
    )

ecm_qt_declare_logging_category(kmail_languagetoolplugin HEADER languagetoolplugin_debug.h IDENTIFIER KMAIL_EDITOR_LANGUAGETOOL_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_languagetoolplugin
    DESCRIPTION "kdepim-addons (languagetool plugin)"
    EXPORT KDEPIMADDONS
    )


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_languagetoolplugin PROPERTIES UNITY_BUILD ON)
endif()

target_link_libraries(kmail_languagetoolplugin
    KF5::MessageComposer KF5::I18n KF5::PimCommon KF5::XmlGui kmaillanguagetool  grammarcommon
    )
