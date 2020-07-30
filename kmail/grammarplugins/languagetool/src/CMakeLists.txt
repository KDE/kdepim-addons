set(kmaillanguagetool_SRCS
    languagetoolparser.cpp
    languagetoolgrammarerror.cpp
    languagetoolresultwidget.cpp
    languagetoolconfigdialog.cpp
    languagetoolconfigwidget.cpp
    languagetoolmanager.cpp
    languagetoolresultjob.cpp
    languagetoolcombobox.cpp
    languagetoolgetlistoflanguagejob.cpp
    languagetoollistoflanguagesparser.cpp
    languageinfo.cpp
    languagetoolupdatecombobox.cpp
    )

ecm_qt_declare_logging_category(kmaillanguagetool_SRCS HEADER liblanguagetool_debug.h IDENTIFIER LIBLANGUAGE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.liblanguagetoolplugin
    DESCRIPTION "kdepim-addons (liblanguagetool)"
    EXPORT KDEPIMADDONS
    )


add_library(kmaillanguagetool ${kmaillanguagetool_SRCS})
generate_export_header(kmaillanguagetool BASE_NAME libkmaillanguagetool)
target_link_libraries(kmaillanguagetool
    KF5::I18n
    KF5::ConfigCore
    KF5::WidgetsAddons
    KF5::KIOWidgets
    grammarcommon
    )

set_target_properties(kmaillanguagetool
    PROPERTIES OUTPUT_NAME kmaillanguagetool VERSION ${KDEPIMADDONS_LIB_VERSION} SOVERSION ${KDEPIMADDONS_LIB_SOVERSION}
    )

install(TARGETS kmaillanguagetool ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)
