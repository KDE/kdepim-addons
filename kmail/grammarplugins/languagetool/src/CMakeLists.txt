# SPDX-FileCopyrightText: 2019-2021 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(kmaillanguagetool)
target_sources(kmaillanguagetool PRIVATE
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

ecm_qt_declare_logging_category(kmaillanguagetool HEADER liblanguagetool_debug.h IDENTIFIER LIBLANGUAGE_PLUGIN_LOG CATEGORY_NAME org.kde.pim.liblanguagetoolplugin
    DESCRIPTION "kdepim-addons (liblanguagetool)"
    EXPORT KDEPIMADDONS
    )



if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmaillanguagetool PROPERTIES UNITY_BUILD ON)
endif()

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
