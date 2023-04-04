# SPDX-FileCopyrightText: 2015-2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

kcoreaddons_add_plugin(kmail_zoomtexteditorplugin SOURCES
    ${kmail_zoomtexteditorplugin_SRCS} INSTALL_NAMESPACE pim6/kmail/plugineditor)
target_sources(kmail_zoomtexteditorplugin PRIVATE
    zoomtextplugineditor.cpp
    zoomtextplugineditorinterface.cpp
    zoomlabel.cpp
    zoomtextplugineditor.h
    zoomtextplugineditorinterface.h
    zoomlabel.h
    )

ecm_qt_declare_logging_category(kmail_zoomtexteditorplugin HEADER zoomtexteditorplugin_debug.h IDENTIFIER KMAIL_EDITOR_ZOOMTEXT_PLUGIN_LOG CATEGORY_NAME org.kde.pim.kmail_zoomtexteditorplugin
    DESCRIPTION "kdepim-addons (kmail zoomtext editor plugins)"
    OLD_CATEGORY_NAMES log_kmail_zoomtexteditorplugin
    EXPORT KDEPIMADDONS
    )



if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(kmail_zoomtexteditorplugin PROPERTIES UNITY_BUILD ON)
endif()


target_link_libraries(kmail_zoomtexteditorplugin
    KPim6::MessageComposer KF6::XmlGui KF6::I18n
    )

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()

