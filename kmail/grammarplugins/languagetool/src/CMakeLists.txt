set(kmaillanguagetool_SRCS
    languagetoolparser.cpp
    languagetoolgrammarerror.cpp
    languagetoolresultwidget.cpp
    languagetoolconfigdialog.cpp
    languagetoolconfigwidget.cpp
    languagetoolmanager.cpp
    languagetoolresultjob.cpp
    languagetoolcombobox.cpp
)

ecm_qt_declare_logging_category(kmaillanguagetool_SRCS HEADER liblanguagetool_debug.h IDENTIFIER LIBLANGUAGE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.liblanguagetoolplugin)

add_library(kmaillanguagetool ${kmaillanguagetool_SRCS})
generate_export_header(kmaillanguagetool BASE_NAME libkmaillanguagetool)
target_link_libraries(kmaillanguagetool
    KF5::I18n
    KF5::IconThemes
    KF5::ConfigCore
    KF5::WidgetsAddons
    KF5::KIOWidgets
    KF5::MessageComposer
    grammarcommon
)
